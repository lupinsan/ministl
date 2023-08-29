#ifndef M_NUMERIC_H
#define M_NUMERIC_H

#include "../mini_memory/mini_memory.h"
#include"../mini_iterator/mini_iter.h"
#include "../algorithm/m_algo.h"

namespace mini
{
template <class InputIterator, class T>
T accumulate(InputIterator first,InputIterator last, T init){
    for(;first!=last;++first){
        init=init+*first;
    }
    return first;
}


template <class InputIterator, class T,class BinaryOperation>
T accumulate(InputIterator first,InputIterator last, T init,BinaryOperation bin_op ){
    for(;first!=last;++first)
        init = bin_op(init,*first);
    return init;
}



template <class InputIterator, class OutputIterator, class T>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*){
    T value = *first;
    while(++first !=last) {
        T tmp = *first;
        *++result = tmp - value;
        value = tmp;
    }
    return ++result;
}

template <class InputInterator, class OutputIterator>
OutputIterator adjacent_difference(InputInterator first,InputInterator last, InputInterator result){
    if(first==last) return result;
    *result = *first;
    return __adjacent_difference(first, last, result, value_type(first));
}


template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result,T*,BinaryOperation bin_op){
    T value = *first;
    while(++first!=last){
        T tmp =* first;
        *++result = bin_op(tmp,value);
        value = tmp;
    }
    return ++result;
}


template <class InputIterator, class OutputIterator ,class BinaryOperation>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation bin_op){
    if(first==last) return result;
    *result = *first;
    return __adjacent_difference(first,last,result,value_type(first),bin_op);
}

template <class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init) {
    for(;first1 !=last1;++first1,++first2)
        init = init + (*first * *first2);
    return init;
}


template <class InputIterator1, class InputIterator2, class T,
        class BinaryOperation1, class BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,T init
        , BinaryOperation1 bin_op1, BinaryOperation2 bin_op2)
{
    for(;first1!=last1;++first1,++first2){
        init = bin_op1(init,bin_op2(*first1,*first2));
    }
    return init;
}


template<class InputIterator, class OutputIterator, class T>
OutputIterator __partial_sum(InputIterator first, InputIterator last, OutputIterator result,T*){
    T value = *first;
    while (++first!=last){
        value = value +*first;
        *++result = value;
    }
    return ++result;
}

template<class InputIterator, class OutputIterator, class T,class BinaryOperation>
OutputIterator __partial_sum(InputIterator first, InputIterator last, OutputIterator result,T*,BinaryOperation bin_op){

    T value = *first;
    while (++first!=last){
        value = bin_op(value,*first);
        *++result = value;
    }
    return ++result;
}

template <class InputIterator, class OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result){
    if(first == last) return result;
    *result = *first;
    return __partial_sum(first,last, result, value_type(first));
}


template <class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation bin_op){
    if(first == last) return result;
    *result = *first;
    return __partial_sum(first,last, result, value_type(first),bin_op);
}



















}
#endif