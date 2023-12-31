#ifndef M_UNORDERED_SET_H
#define M_UNORDERED_SET_H
#include "../hashtable/m_hashtable.h"
#include"../functions/m_functor.h"

namespace mini
{

template <class Value, class HashFcn =mini::hash<Value>, class EqualKey =mini::equal_to<Value>,class Alloc = __malloc_alloc>
class hash_set
{
private:
    typedef hashtable<Value,Value,HashFcn, identity<Value>,EqualKey,Alloc> ht;
    ht rep;

public:
    typedef typename ht::key_type key_type;
    typedef typename ht::value_type value_type;
    typedef typename ht::hasher hasher;
    typedef typename ht::key_equal key_equal;

    typedef typename ht::size_type size_type;
    typedef typename ht::difference_type difference_type;
    typedef typename ht::pointer pointer;
    typedef typename ht::const_pointer const_pointer;
    typedef typename ht::const_reference reference;
    typedef typename ht::const_reference const_reference;

    typedef typename ht::iterator iterator;
    typedef typename ht::const_iterator const_iterator;

    //hasher hash_funct() const {return rep.hash}
    //key_equal key_eq() const {return }

public:
    hash_set(): rep(100,hasher(),key_equal()){}
    explicit hash_set(size_type n): rep(n,hasher(),key_equal()){}
    hash_set(size_type n,const hasher& hf): rep(n, hf, key_equal()){}
    hash_set(size_type n, const hasher& hf,const key_equal& eql)
        : rep(n,hf,eql) {}
    
    template <class InputIterator>
        hash_set(InputIterator f, InputIterator l)
            : rep(100,hasher(), key_equal()) {rep.insert_unique(f,l); }
    
    template <class InputIterator>
        hash_set(InputIterator f,InputIterator l,size_type n, const hasher& hf)
            : rep(n, hf, key_equal()) {rep.insert_unique(f,l); }
    
    template <class InputIterator>
        hash_set(InputIterator f, InputIterator l, size_type n, const hasher& hf, const key_equal& eql)
            :rep(n,hf, eql) {rep.insert_unique(f,l); }

public:
    size_type size() const {return rep.size(); }
    size_type max_size() const {return rep.max_buck_count(); }
    bool empty() const {return rep.empty(); }
    void swap(hash_set& hs) {rep.swap(hs.rep); }
    //==
    
    iterator begin() const { return rep.begin(); }
    iterator end() const { return rep.end(); }

public:
    pair<iterator, bool> insert(const value_type& obj)
    {
        pair<typename ht::iterator, bool>p = rep.insert_unique(obj);
        return pair<iterator, bool>(p.first,p.second);
    }
    
    template<class InputIterator>
    void insert(InputIterator f,InputIterator l) {
        rep.insert_unique(f,l);
    }
    //pair<iterator, bool> insert_no

    iterator find(const key_type& key) const {return rep.find(key); }
    size_type count(const key_type& key) const {return rep.count(key); }

    size_type erase(const key_type& key) {return rep.erase(key);}
    size_type erase(iterator it) {return rep.erase(it); }

    void clear() {rep.clear(); }

public:
    void resize(size_type hint) {rep.resize(hint) ;}
    size_type bucket_count() const {return rep.bucket_count(); }
    size_type max_bucket_count() const {return rep.max_buck_count(); }
    //size_type elems_in_bucket(size_type n) const {return rep.num_elements; }



};
}
#endif