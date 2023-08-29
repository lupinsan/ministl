#ifndef M_ALGOBASE_H
#define M_ALGOBASE_H
#include "../mini_memory/mini_memory.h"
#include"../mini_iterator/mini_iter.h"
#include"../pair/m_pair.h"

namespace mini{


template <class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,InputIterator1 last1, InputIterator2 first2){
    for(;first1 !=last1;++first1,++first2){
        if(*first1!=*first2)
            return false;
    }
    return true;
}


template <class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first1, InputIterator1 last1, 
                InputIterator2 first2, BinaryPredicate bin_pre){
    for(;first1!=last1;++first1,++first2){
        if(!bin_pre(*first1,*first2))
            return false;
    }
    return true;
}

template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value){
    for(;first!=last;++first)
        *first = value;
}

template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value){
    for(;n>0;--n,++first)
        *first = value;
    return first;
}

template <class ForwardIterator1, class ForwardIteraotr2, class T>
inline void iter_swap(ForwardIterator1 a, ForwardIteraotr2 b,T*){
    T tmp = *a;
    *a = *b;
    *b = tmp;
}


template <class ForwardIterator1, class ForwardIteraotr2>
inline void iter_swap(ForwardIterator1 a, ForwardIteraotr2 b){
    __iter_swap(a,b,value_type(a));
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
    for(;first1!=last1&&first2!=last2;++first1,++first2) {
        if(*first1<*first2)     
            return true;
        if(*first2<*first1)
            return false;
    }
    return first1==last1&&first2!=last2;
}

template <class InputIterator1, class InputIterator2,class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp){
    for(;first1!=last1&&first2!=last2;++first1,++first2) {
        if(comp(*first1,*first2))     
            return true;
        if(comp(*first2,*first1))
            return false;
    }
    return first1==last1&&first2!=last2;
}


template <class T>
inline const T& max(const T& a,const T& b) {
    return a<b?b:a;
}

template <class T, class Compare>
inline const T& max(const T& a,const T& b, Compare comp){
    return comp(a,b)?b:a;
}

template <class T>
inline const T& min(const T& a,const T& b){
    return b<a?b:a;
}

template <class T,class Compare>
inline const T& min(const T& a,const T& b,Compare comp){
    return comp(b,a)?b:a;
}

template <class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2){
    while (first1!=last1 && *first1==*first2)
    {
        ++first1;
        ++first2;
    }
    return pair<InputIterator1,InputIterator2>(first1,first2);
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,BinaryPredicate bin_pred){

    while (first1!=last1 && bin_pred(*first1,*first2))
    {
        ++first1;
        ++first2;
    }
    return pair<InputIterator1,InputIterator2>(first1,first2);
}


template <class T>
inline void swap(T& a,T& b){
    T tmp =a;
    a=b;
    b=tmp;
}
















}
#endif