#ifndef M_SET_H
#define M_SET_H
#include "../RB-tree/m_rb_tree.h"
#include"../functions/m_functor.h"



namespace mini{

template <class Key, class Compare = less<Key> , class Alloc=__malloc_alloc>
class set{
public:
    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;

private:

    typedef rb_tree<key_type,value_type,identity<value_type>,key_compare,Alloc> rep_type;
    
    rep_type t;

//identity;

public:
    typedef typename rep_type::const_pointer pointer;
    typedef typename rep_type::const_pointer const_pointer;
    typedef typename rep_type::const_reference reference;
    typedef typename rep_type::const_reference const_reference;
    typedef typename rep_type::const_iterator   iterator;
    typedef set<Key,Compare,Alloc>  self;


    typedef typename rep_type::const_iterator   const_iterator;
    //
    //...reverse
    //
    typedef typename rep_type::size_type    size_type;
    typedef typename rep_type::difference_type  difference_type;


    set(): t(Compare()) {}
    
    explicit set(const Compare& comp) : t(comp) {}

    template <class InputIterator>
    set(InputIterator first, InputIterator last) : t(Compare()){t.insert_unique(first,last);}

    set(const self& x): t(x.t) {}
    self& operator= (const self& x) {//-------------------------
        t = x.t;
        return *this;
    }



    key_compare key_comp() const {return t.key_comp();}

    value_compare value_comp() const {return t.key_comp();}


    iterator begin() const {return t.begin();}

    iterator end() const {return t.end();}

    //
    //...
    //

    bool empty() const {return t.empty();}
    size_type size() const {return t.size();}
    size_type max_size() const {return t.max_size();}
    void swap(self& x) {t.swap(x.t);}//-------------------------

    iterator find(const key_type& x) const { return t.find(x); }

    typedef pair<iterator,bool> pair_iterator_bool;
    pair_iterator_bool insert(const value_type& x){
        auto x1 = t.insert_unique(x);
        //decltype(t.insert_unique(x)) x1 = t.insert_unique(x);
        typename rep_type::iterator ite = x1.first;
        return pair<iterator,bool>(ite,x1.second);
    }

    template <class InputIterator>
    void insert(InputIterator first,InputIterator last){
        t.insert_unique(first,last);
    }

    void erase(iterator position){
        typedef typename rep_type::iterator rep_iterator;
        t.erase((rep_iterator&)position);
    }

    void erase(const key_type& x){
        auto x1 = find(x);
        if(x1!=t.end())
            t.erase(x1);
        return;
    }
    void erase(iterator first,iterator last) {
        typedef typename rep_type::iterator rep_iterator;
        for(;first!=last;++first){
            t.erase((rep_iterator&)first);
        }
        return;
    }

    void clear() {t.clear();}

    //size_type count(const key_type& x) const {return t.count(x);}

    // iterator lower_bound(const key_type& x) const {
    //     return t.lower_bound(x);
    // }

    // iterator upper_bound(const key_type& x) const {
    //     return t.upper_bound(x);
    // }

    





    

};


}











#endif