#ifndef M_FUNCTOR_H
#define M_FUNCTOR_H
#include <cstddef>
#include "../m_type.h"




namespace mini
{


template <class Arg, class Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};








template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result Result_type;
};

template <class T>
struct equal_to:public binary_function<T,T,bool>{
    bool operator()(const T&x, const T& y) const {return x==y; }
};



template <class T>
struct less : public binary_function<T,T,bool> {
    bool operator()(const T& x,const T& y) const { return x<y; }
};


template <class T>
struct identity :public unary_function<T,T> {
    const T& operator() (const T& x) const {return x;}
};

template <class Key> 
struct hash{};

inline size_t __stl_hash_string(const char* s){
    unsigned long h = 0;
    for(;*s;++s)
        h = 5*h+*s;
    return size_t(h);
}
template <>
struct hash<char*>{
    size_t operator()(const char* s)const {return __stl_hash_string(s); }
};
template <>
struct hash<const char*>{
    size_t operator()(const char* s)const {return __stl_hash_string(s); }
};
template <>
struct hash<char>{
    size_t operator()(char x)const {return size_t(x); }
};
template <>
struct hash<unsigned char>{
    size_t operator()(unsigned char x)const {return size_t(x); }
};
template <>
struct hash<signed char>{
    size_t operator()(unsigned char x)const {return size_t(x); }
};
template <>
struct hash<unsigned short>{
    size_t operator()(unsigned short x)const {return size_t(x); }
};
template <>
struct hash<int>{
    size_t operator()(int x)const {return size_t(x); }
};
template <>
struct hash<unsigned int>{
    size_t operator()(unsigned int x)const {return size_t(x); }
};
template <>
struct hash<long>{
    size_t operator()(long x)const {return size_t(x); }
};
template <>
struct hash<unsigned long>{
    size_t operator()(unsigned long x)const {return size_t(x); }
};


template <class Pair>
struct select1st: public unary_function<Pair, typename Pair::first_type>
{
    const typename Pair::first_type& operator()(const Pair& x)const{
        return x.first;
    }
};







}
#endif