#ifndef M_STACK_H
#define M_STACK_H

#include"../mini_iterator/mini_iter.h"
#include"../mini_memory/mini_memory.h"
#include"../algorithm/m_algo.h"
#include"../deque/m_deque.h"


namespace mini
{

template <class T,class Sequence = deque<T>>
class stack{
public:
    typedef typename Sequence::value_type   value_type;
    typedef typename Sequence::size_type   size_type;
    typedef typename Sequence::reference   reference;
    typedef typename Sequence::const_reference   const_reference;
protected:
    Sequence c;
public:
    
    


    
    
    
    bool empty() const {return c.empty();}
    size_type size() const {return c.size();}
    reference top() {return c.back();}
    const_reference top() const {return c.back();}
    void push(const value_type& x)  { c.push_back(x); }
    void pop() {c.pop_back();}
};




}

#endif