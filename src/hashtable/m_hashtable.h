#ifndef M_HASHTABLE_H
#define M_HASHTABLE_H
#include"../mini_iterator/mini_iter.h"
#include"../mini_memory/mini_memory.h"
#include"../algorithm/m_algo.h"
#include"../vector/m_vector.h"
#include"../pair/m_pair.h"
#include <iostream>

namespace mini
{

static const int __stl_num_primes = 15;
static const unsigned long __stl_prime_list[__stl_num_primes] =
{
    53,97,193,389,769,
    1543,3079,6151,12289,24593,
    49157,98317,196613,393241,786433
};

inline unsigned long __stl_next_prime(unsigned long n){
    const unsigned long* first = __stl_prime_list;
    const unsigned long* last = __stl_prime_list+ __stl_num_primes;
    const unsigned long* pos = lower_bound(first,last,n);

    return pos == last? *(last-1):*pos;
}




template <class Value>
struct __hashtable_node{
    __hashtable_node* next;
    Value val;
};

template <class Value, class Key, class HashFcn,class ExtractKey,class EqualKey, class Alloc=__malloc_alloc>
class hashtable;



template <class Value, class Key, class HashFcn,class ExtractKey,class EqualKey, class Alloc>
struct __hashtable_iterator {
public:
    typedef  hashtable<Value,Key,HashFcn,ExtractKey,EqualKey,Alloc> hashtable1;
    typedef __hashtable_iterator<Value,Key,HashFcn,ExtractKey,EqualKey,Alloc> iterator;
    typedef __hashtable_iterator<Value,Key,HashFcn,ExtractKey,EqualKey,Alloc> const_iterator;
    typedef __hashtable_node<Value> node;

    typedef forward_iterator_tag iterator_category;
    typedef Value   value_type;
    typedef ptrdiff_t   difference_type;
    typedef size_t  size_type;
    typedef Value&  reference;
    typedef Value*  pointer;

    node* cur;
    hashtable1* ht;

    __hashtable_iterator(node* n, hashtable1* tab): cur(n),ht(tab){}
    __hashtable_iterator() {}
    __hashtable_iterator(const iterator& x){cur = x.cur; ht=x.ht;}
    reference operator*() const { return cur->val; }
    pointer operator->() const {return &(operator*()); } 
    iterator& operator++();
    iterator& operator++(int){
        iterator tmp = *this;
        ++*this;
        return tmp;
    }
    bool operator==(const iterator& it)const {return cur==it.cur; }
    bool operator!=(const iterator& it)const {return cur!=it.cur; }
    iterator& operator=(const iterator& it){
        cur=it.cur;
        ht=it.ht;
        return *this;
    }

};





template <class Value, class Key, class HashFcn,class ExtractKey,class EqualKey, class Alloc>
class hashtable{
    
public:
    friend class __hashtable_iterator<Value,Key,HashFcn,ExtractKey,EqualKey,Alloc>;
    typedef __hashtable_iterator<Value,Key,HashFcn,ExtractKey,EqualKey,Alloc> iterator;
    typedef HashFcn hasher;
    typedef EqualKey key_equal;
    typedef size_t  size_type;
    typedef Value   value_type;
    typedef Key     key_type;
    typedef ptrdiff_t   difference_type;
    typedef Value*  pointer;
    typedef const Value*  const_pointer;
    typedef Value& reference;
    typedef const Value& const_reference;
    typedef const iterator const_iterator;




private:
    hasher hash;
    key_equal equals;
    ExtractKey get_key;

    typedef __hashtable_node<Value> node;
    typedef simple_alloc<node,Alloc> node_allocator;

    vector<node*,Alloc> buckets;
    size_type num_elements;

public:
    size_type max_buck_count() const{
        return __stl_prime_list[__stl_num_primes -1];
    }
    size_type bucket_count() const {return buckets.size(); }
    size_type size() const {return num_elements; }

    iterator begin(){
        int bucket=0;
        node* cur1=buckets[bucket];
        while(++bucket<this->buckets.size()&&!cur1){
            cur1=buckets[bucket];
        }
        return iterator(cur1,this);
    }

    iterator end(){//最后一位
        int bucket =buckets.size()-1;
        node* cur1 = buckets[bucket];
        while(--bucket>=0&&!cur1){
            cur1 = buckets[bucket];
        }
        while(cur1->next){
            cur1=cur1->next;
        }
        return iterator(cur1,this);
    }

    bool empty(){
        return num_elements==0;
    }




    node* new_node(const value_type& obj)
    {
        node* n;
        try{
            n = node_allocator::allocate();
            n->next = 0;
            construct(&n->val,obj);
            return n;
        }
        catch(...){
            destroy(&n->val);
            node_allocator::deallocate(n);
        }
    }

    void delete_node(node* n){
        destroy(&n->val);
        node_allocator::deallocate(n);
    }





    size_type next_size(size_type n) const {
        return __stl_next_prime(n);
    }

    void initialize_buckets(size_type n){
        const size_type n_buckets = next_size(n);//--------------------
        buckets.reserve(n_buckets);
        buckets.insert(buckets.begin(),n_buckets,(node*) 0);
        num_elements = 0;
    }

        
    hashtable(size_type n,const HashFcn& hf, const EqualKey& eql):hash(hf),equals(eql),get_key(ExtractKey()),num_elements(0)//直接调用构造为何可以？
    {
        initialize_buckets(n);
    }


    size_type bkt_num_key(const key_type& key, size_type n)const{
        return hash(key) % n;
    }

    size_type bkt_num_key(const key_type& key)const{
        return bkt_num_key(key,buckets.size());
    }


    size_type bkt_num(const value_type& obj, size_t n)const
    {
        return bkt_num_key(get_key(obj), n);
    }
    size_type bkt_num(const value_type& obj)const
    {
        return bkt_num_key(get_key(obj));
    }


    void resize(size_type num_elements_hint){
        const size_type old_n = buckets.size();
        if (num_elements_hint >old_n){
            const size_type n = next_size(num_elements_hint);
            if(n>old_n){
                vector<node*,Alloc> tmp(n,(node*)0);
                try{
                    for(size_type bucket = 0;bucket < old_n;++bucket) {
                        node* first = buckets[bucket];
                        while(first){
                            size_type new_bucket = bkt_num(first->val, n);
                            buckets[bucket] = first->next;
                            first->next = tmp[new_bucket];
                            tmp[new_bucket] = first;
                        }
                    }
                    buckets.swap(tmp);//------
                }
                catch(...){
                    abort();
                }
            }
        }
    }

    pair<iterator,bool> insert_unique_noresize(const value_type& obj)
    {
        const size_type n = bkt_num(obj);
        node* first = buckets[n];

        for(node* cur=first;cur;cur = cur->next)
            if(equals(get_key(cur->val), get_key(obj)))
                return pair<iterator, bool>(iterator(cur,this),false);
        
        node* tmp =new_node(obj);
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
        return pair<iterator,bool>(iterator(tmp,this),true);
    }

    pair<iterator,bool> insert_unique(const value_type& obj){
        resize(num_elements+1);
        return insert_unique_noresize(obj);
    }

    iterator insert_equal_noresize(const value_type& obj){
        const size_type n = bkt_num(obj);
        node* first = buckets[n];

        for(node* cur = first;cur;cur=cur->next)
        {
            if( equals(get_key(cur->val),get_key(obj))) {
                node* tmp = new_node(obj);
                tmp->next = cur->next;
                cur->next = tmp;
                ++num_elements;
                return iterator(tmp,this);
            }
        }
        node* tmp = new_node(obj);
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
        return iterator(tmp,this);
    }

    iterator insert_equal(const value_type& obj){
        resize(num_elements + 1);
        return insert_equal_noresize(obj);
    }

    void clear(){
        for(size_type i =0;i<buckets.size();++i){
            node* cur = buckets[i];
            while(cur!=0){
                node* next = cur->next;
                delete_node(cur);
                cur=next;
            }
            buckets[i] = 0;
        }
        num_elements = 0;
    }

    void copy_from(const hashtable& ht){
        //buckets.clear();
        buckets.reserve(ht.buckets.size());
        buckets.insert(buckets.end(),ht.buckets.size(),(node*)0);
        try{
            for(size_type i =0;i<ht.buckets.size();++i){
                if(const node* cur = ht.buckets[i]){
                    node* copy = new_node(cur->val);
                    buckets[i] = copy;

                    for(node* next = cur->next;next;cur=next,next=cur->next) {
                        copy->next = new_node(next->val);
                        copy = copy->next;
                    }
                }
            }
            num_elements = ht.num_elements;
        }
        catch(...){
            clear();
        }
        return;
    }

    iterator find(const key_type& key){
        size_type n = bkt_num_key(key);
        node* first;
        for(first = buckets[n];first && !equals(get_key(first->val), key);first = first->next){}
        return iterator(first, this);
    }

    size_type count(const key_type& key) 
    {
        const size_type n = bkt_num_key(key);
        size_type result = 0;
        for( node* cur =buckets[n];cur;cur=cur->next){
            if(equals(get_key(cur->val), key))
                ++result;
        }
        return result;
    }

    void erase(iterator it) {   
        int i = bkt_num(it->cur->val);
        node* ptr = buckets[i];
        if(ptr==it->cur){
            buckets[i] = buckets[i]->next;
            delete_node(it->cur);
            return;
        }

        while(ptr->next!=it->cur){
            ptr=ptr->next;
        }
        
        ptr->next=ptr->next->next;
        delete_node(it->cur);
        return;
    }




    void erase(const key_type& key){
        
        int i = bkt_num_key(key);
        node* ptr =buckets[i];
        if(ptr==0){
            return;
        }
        else{
            buckets[i]=ptr->next;
            num_elements-=1;
            delete_node(ptr);
        }

        return;
    }

    value_type& find_or_insert(const value_type& val ){
        iterator it = find(get_key(val));
        if(it.cur == 0){
            return  insert_equal(val).cur->val;
        }
        else{
            return it.cur->val;
        }
    }





};




template <class V,class K,class HF, class ExK, class EqK, class A>
__hashtable_iterator<V,K,HF,ExK,EqK,A>&
__hashtable_iterator<V,K,HF,ExK,EqK,A>::operator++(){
    const node* old = cur;
        cur=cur->next;
        if(!cur){
            size_type bucket = ht->bkt_num(old->val);
            while(!cur&&++bucket<ht->bucket_count())
                cur = ht->buckets[bucket];
        }
    return *this;
}
}
#endif