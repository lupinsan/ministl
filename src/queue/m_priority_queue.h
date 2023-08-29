#ifndef M_QUEUE_H
#define M_QUEUE_H


#include"../mini_iterator/mini_iter.h"
#include"../mini_memory/mini_memory.h"
#include"../algorithm/m_algo.h"
#include"../deque/m_deque.h"
#include"../vector/m_vector.h"
namespace mini
{
template <class T,class Sequence = vector<T>, class Compare>
class priority_queue{
public:
    typedef typename Sequence::value_type   value_type;
    typedef typename Sequence::size_type    size_type;
    typedef typename Sequence::reference    reference;
    typedef typename Sequence::const_reference const_reference;

protected:
    Sequence c;
    Compare comp;

public:
    priority_queue(): c(){}
    explicit priority_queue(const Compare& x): c(),comp(x) {}

    template<class InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare& x)
        :c(first,last),comp(x){make_heap(c.begin(),c.end(),comp);}
    
    template<class InputIerator>
    priority_queue(InputIerator first, InputIerator last)
        :c(first,last) {make_heap(c.begin(),c.end(),comp);}

    bool empty() const {return c.empty();}
    size_type size() const {return c.size();}
    const_reference top() const {return c.front();}
    void push(const value_type& x){
        c.push_back(x);
        push_heap(c.begin(),c.end(),comp);
    }
    void pop(){
        pop_heap(c.begin(),c.end(),comp);
        c.pop_back();
    }
};




}
#endif