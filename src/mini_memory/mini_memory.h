#ifndef MINI_MEMORY_H
#define MINI_MEMORY_H

#include<memory>
#include <new>
#include<stdlib.h>

//
#include "../mini_iterator/mini_iter.h"
#include "../m_type.h"
////////////////////////////construct

template<class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last,__false_type)
{
    for(;first<last;++first)
    {
        destroy(&*first);
    }
}

template<class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last,__true_type){}



template <class T1, class T2>//具有深复制能力
inline void construct(T1* p, T2& value)
{
    new(p) T1(value);
}

template <class T>
inline void destroy(T* pointer)
{
    pointer->~T();
}

inline void destroy(char* ){}


template<class ForwardIterator,class T>
inline void __destroy(ForwardIterator first,ForwardIterator last,T*)
{
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    __destroy_aux(first,last,trivial_destructor());
}


template <class ForwardIterator>
inline void destroy(ForwardIterator first,ForwardIterator last){
    __destroy(first,last,value_type(first));
}



/////////////////////////////////////////////////


template <class InputIterator, class ForwardIterator>//暂时不支持重叠区间以及加速
ForwardIterator uninitialized_copy(InputIterator first ,InputIterator last,ForwardIterator res)
{
    ForwardIterator cur = res;
    for(;first!=last;++cur,++first){
        construct(&*cur,*first);
    }
    return cur;
}


template<class ForwardIterator,class T>
ForwardIterator uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x)
{
    ForwardIterator cur=first;
    for(;cur!=last;++cur)
    {
        construct(&*cur,x);
    }
    return cur;
}



template<class ForwardIterator,class Size,class T>//暂时不支持加速
ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first,Size n,const T& x,__true_type){
    ForwardIterator cur = first;
    for(;n>0;cur++,n--)
    {
        construct(&*cur,x);
    }
    return cur;
}

template<class ForwardIterator,class Size,class T>
ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first,Size n,const T& x,__false_type){
    ForwardIterator cur = first;
    for(;n>0;cur++,n--)
    {
        construct(&*cur,x);
    }
    return cur;
}

template<class ForwardIterator,class Size,class T,class T1>
ForwardIterator
__uninitialized_fill_n(ForwardIterator first,Size n,const T& x,T1*){
    
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return __uninitialized_fill_n_aux(first,n,x,is_POD());

}



template<class ForwardIterator,class Size,class T>
ForwardIterator
uninitialized_fill_n(ForwardIterator first,Size n,const T& x){
    return __uninitialized_fill_n(first,n,x,value_type(first));
}

//////////////////////////////
class __malloc_alloc
{

    public:
    static void* allocate(size_t n)
    {
        void * res = malloc(n);
        if(0 == res)
        {
            //res =
            //for the malloc failure 
        }
        return res;
    }

    static void deallocate(void* p)
    {
        free(p);
    }

};


template<class T,class Alloc=__malloc_alloc>
class simple_alloc
{
    public:
    static T* allocate(size_t n)
    {
        return(T*) (0==n? 0:Alloc::allocate(n*sizeof(T)));
    }
    static T* allocate()
    {
        return (T*) Alloc::allocate(sizeof(T));
    }
    static void deallocate(T* p,size_t n)
    {
        if(n!=0)
            Alloc::deallocate(p);
    }
    static void deallocate(T* p)
    {
        Alloc::deallocate(p);
    }

};




#endif