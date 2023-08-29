#ifndef M_MUTISET_H
#define M_MUTISET_H
#include "../RB-tree/m_rb_tree.h"
#include"../functions/m_functor.h"

namespace mini
{

template <class Key, class Compare=less<Key>, class Alloc = __malloc_alloc>
class mutiset {
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
    typedef mutiset<Key,Compare,Alloc>  self;


    typedef typename rep_type::const_iterator   const_iterator;
    //
    //...reverse
    //
    typedef typename rep_type::size_type    size_type;
    typedef typename rep_type::difference_type  difference_type;

    mutiset(): t(Compare()) {}
    
    explicit mutiset(const Compare& comp) : t(comp) {}

    template <class InputIterator>
    mutiset(InputIterator first, InputIterator last) : t(Compare()){t.insert_equal(first,last);}

    mutiset(const self& x): t(x.t) {}
    self& operator= (const self& x) {//-------------------------
        t = x.t;
        return *this;
    }










};
}
#endif