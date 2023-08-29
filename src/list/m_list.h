#ifndef M_LIST_H
#define M_LIST_H
#include"../mini_iterator/mini_iter.h"
#include"../mini_memory/mini_memory.h"
#include"../algorithm/m_algo.h"


namespace mini
{

template <class T>
struct __list_node{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template<class T,class Ref,class Ptr>
struct __list_iterator{
public:
    typedef __list_iterator<T,T&,T*>    iterator;
    typedef __list_iterator<T,Ref,Ptr>    self;

    //内嵌型别

    typedef bidirectional_iterator_tag iterator_category;
    typedef T   value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T>* link_type;
    typedef size_t  size_type;
    typedef ptrdiff_t   difference_type;

    link_type node;


    __list_iterator(link_type x): node(x){}
    __list_iterator() {}
    __list_iterator(const iterator& x): node(x.node) {}//重载等于 =?

    bool operator==(const iterator& x) const {return node == x.node;}//-------------
    bool operator!=(const iterator& x) const {return node != x.node;}

    reference operator*() const {return (*node).data; }
    pointer operator->() const { return &(*this); }//------

    self& operator++(){
        node = (link_type)(node->next);
        return *this;
    }

    self operator++(int){
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self& operator--(){
        node = (link_type)(node->prev);
        return *this;
    }

    self operator--(int){
        self tmp = *this;
        --*this;
        return tmp;
    }
};

template <class T,class Alloc = __malloc_alloc>
class list{
public:
    typedef T           value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   defference_type;
    typedef __list_iterator<value_type,reference,pointer>   iterator;

    typedef list<T,Alloc> self;

protected:
    typedef __list_node<T>  list_node;

public:
    typedef list_node*  link_type;

protected:
    link_type node;
    
    typedef simple_alloc<list_node, Alloc>  list_node_allocator;
    link_type get_node(){return list_node_allocator::allocate(); }
    void put_node(link_type p) {list_node_allocator::deallocate(p);}
    link_type create_node(const T& x){
        link_type p =get_node();
        construct(&(p->data),x);
        return p;
    }
    void destroy_node(link_type p){
        destroy(&(p->data));
        put_node(p);
    }
    void empty_initialize(){
        node = get_node();
        node->next = node;
        node->prev = node;
    }



public:
    iterator begin() const {return iterator(link_type(node->next)); }
    iterator end() const {return iterator(link_type(node)); }
    size_type size() const {
        size_t n=0;
        iterator beg = begin();
        iterator fin = end();
        for(;beg!=fin;++beg){
            ++n;
        }
        return n;
    }
    bool empty() const{return begin()==end();}

    void clear(){
        link_type cur = (link_type)node->next;
        while(cur!=node){
            link_type tmp = cur;
            cur = (link_type) cur->next;
            destroy_node(tmp);
        }
        node->next = node;
        node->prev = node;
    }


protected:
    void transfer(iterator position, iterator first,iterator last) {
        for(iterator i = first; i!=last; ++i){//----------------------避免position在first与last区间中的情况
            if(i==position)
                return;
        }
        if(position != last){
            (link_type(last.node->prev))->next = position.node;
            (link_type(first.node->prev))->next = last.node;
            (link_type(position.node->prev))->next = first.node;
            link_type tmp = link_type(position.node->prev);
            position.node->prev = last.node->prev; 
            last.node->prev = first.node->prev;
            first.node->prev = tmp;
        }
    }

public:

    list() {empty_initialize(); }
    
    ~list() {
        clear();
        destroy(node);
    }
    
    list(const list& l){
        link_type beg = l.node;
        node = create_node(l.node->data);
        link_type beg1 = node;
        for(beg=link_type(beg->next);beg!=l.node;beg=link_type(beg->next)){
            link_type tmp =create_node(beg->data);
            tmp->prev = beg1;
            beg1->next = tmp;
            beg1=link_type(beg1->next);
        }
        beg1->next = node;
        node->prev = beg1;
    }
    
    list( list&& l)noexcept{
        empty_initialize(); 
        transfer(end(),l.begin(),l.end());

    }
    
    list& operator=(const list& l){
        clear();
        link_type beg = l.node;
        link_type beg1 = node;
        for(beg=link_type(beg->next);beg!=l.node;beg=link_type(beg->next)){
            link_type tmp =create_node(beg->data);
            tmp->prev = beg1;
            beg1->next = tmp;
            beg1=link_type(beg1->next);
        }
        beg1->next = node;
        node->prev = beg1;
        return *this;
    }

    list& operator=(list&& l){
        clear();
        transfer(end(),l.begin(),l.end());
        return *this;
    }

    




    // list(const self& x){//-----------------------------
    // }


    iterator insert(iterator position, const T& x){
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;

        (link_type(position.node->prev))->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }

    void push_back(const T& x){ insert(end(),x);}
    void push_front(const T& x){ insert(begin(),x);}

    iterator erase(iterator position){
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }

    void pop_front() {erase(begin()); }
    void pop_back() {
        iterator tmp =end();
        erase(--tmp);
    }

    

    void remove(const T& value){
        iterator first = begin();
        iterator last = end();
        while(first!=last){
            iterator next = first;
            ++next;
            if(*first == value) erase(first);
            first = next;
        }
    }

    void unique(){
        iterator first =begin();
        iterator last = end();
        if(first==last) return;
        iterator next = first;
        while(++next!=last){
            if(*next == *first)
                erase(next);
            else
                first = next;
            next = first;
        }
    }



public:
    void splice(iterator position, list& x){
        if(!x.empty())
            transfer(position, x.begin(),x.end());
    }

    void splice(iterator position, list&, iterator i){
        iterator j=i;
        ++j;
        if(position == i || position == j) return;
        transfer(position,i,j); 
    }

    void splice(iterator position, list&,iterator first,iterator last){
        if(first!= last){
            transfer(position,first,last);
        }
    }


    void merge(self x){//需要先经过递增排序
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = x.begin();
        iterator last2 = x.end();

        while(first1 != last1 && first2 != last2){
            if(*first2<*first1){
                iterator next = first2;
                next++;
                transfer(first1,first2,next);
                first2 = next;
            }
            else{
                ++first1;
            }
        }
        if(first2!=last2) transfer(last1,first2,last2);
    }

    void reverse() {
        if(node->next == node || link_type(node->next)->next == node)
            return;
        iterator first = begin();
        ++first;
        while(first !=end()){
            iterator old = first;
            ++first;
            transfer(begin(),old,first);
        }
    }


    void swap(list& b){
        if(b.empty()){
            b.transfer(b.end(),begin(),end());
            return;
        }
        if(empty()){
            transfer(end(),b.begin(),b.end());
            return;
        }
        iterator b_data_end = --b.end();
        b.transfer(b.end(),begin(),end());
        transfer(end(),b.begin(),++b_data_end);
    }


};

}








#endif
