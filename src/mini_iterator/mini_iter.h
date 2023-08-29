#ifndef MINI_ITER_H
#define MINI_ITER_H

struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : public input_iterator_tag {};//output???
struct bidirectional_iterator_tag: public forward_iterator_tag{};
struct random_access_iterator_tag: public bidirectional_iterator_tag{};


#include <cstddef>
#include "../m_type.h"
#include "./mini_iter.h"





template<class Category,
        class T,
        class Distance = ptrdiff_t,
        class Pointer =T*,
        class Reference = T&>

 struct iterator{
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
 };


template <class Iterator>//为了适应原生指针而创建
 struct iterator_traits{
    typedef typename Iterator::iterator_category   iterator_category;
    typedef typename Iterator::value_type          value_type;
    typedef typename Iterator::difference_type    difference_type;
    typedef typename Iterator::pointer     pointer;
    typedef typename Iterator::reference   reference;
 };

template <class T>//偏特化,副模板
 struct iterator_traits<T*> {
    typedef random_access_iterator_tag  iterator_category;
    typedef T         value_type;
    typedef ptrdiff_t    difference_type;
    typedef T*    pointer;
    typedef T&   reference;
 };

template <class T>//偏特化,副模板
 struct iterator_traits<const T*> {
    typedef random_access_iterator_tag  iterator_category;
    typedef T         value_type;
    typedef ptrdiff_t    difference_type;
    typedef T*    pointer;
    typedef T&   reference;
 };



template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator& ){
        return typename iterator_traits<Iterator>::iterator_category() ;
    }

template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator& ){
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0) ;
    }

template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator& ){
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0) ;
    }



template <class type>
struct __type_traits{
    typedef __true_type     this_dummu_member_must_be_first;

    typedef __false_type    has_trivial_default_constructor;
    typedef __false_type    has_trivial_copy_constructor;
    typedef __false_type    has_trivial_assignment_operator;
    typedef __false_type    has_trivial_destructor;
    typedef __false_type    is_POD_type;
};

template <>
struct __type_traits<char>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};
template <>
struct __type_traits<unsigned char>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};
template <>
struct __type_traits<signed char>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};
template <>
struct __type_traits<short>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};
template <>
struct __type_traits<unsigned short>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};



template <>
struct __type_traits<int>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};

template <>
struct __type_traits<unsigned int>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};

template <>
struct __type_traits<long>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};

template <>
struct __type_traits<unsigned long>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};
template <>
struct __type_traits<float>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};
template <>
struct __type_traits<double>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};
template <>
struct __type_traits<long double>{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;
};

template <class T>
struct __type_traits<T*>
{
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type; 
};






/////////////////////////////



template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type __distance(
        InputIterator first,InputIterator last,input_iterator_tag){
            typename iterator_traits<InputIterator>::difference_type n=0;//typename
            while(first!=last)
            {
                ++first,++n;
            }
            return n;
} 

template <class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type __distance(
        RandomAccessIterator first,RandomAccessIterator last,random_access_iterator_tag ){
            
            return last-first;
} 


template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type diatance(
    InputIterator first, InputIterator last){
        typedef typename iterator_traits<InputIterator>::iterator_category category;

        return __distance(first,last,category());
}


template <class IuputIterator,class Distance>
inline void __advance(IuputIterator first,Distance n,input_iterator_tag ){
    while(n--) ++first;
}

template <class BidirectionalIterator,class Distance>
inline void __advance(BidirectionalIterator first,Distance n,bidirectional_iterator_tag ){
    if(n>=0)
        while(n--) ++first;
    else
        while(n++) --first;
}

template <class RandomAccessIterator,class Distance>
inline void __advance(RandomAccessIterator first,Distance n,random_access_iterator_tag ){
    
    first+=n;
}

template <class InputIterator,class Distance>
inline void advance(InputIterator first,Distance n){
    
    __advance(first,n,iterator_category(first));
}



#endif