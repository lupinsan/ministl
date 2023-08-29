#ifndef M_PAIR_H
#define M_PAIR_H
namespace mini
{

template<class T1,class T2>
struct pair{
    typedef T1 first_type;
    typedef T2 second_type;

    pair(T1 x1,T2 x2){
        first=x1;
        second =x2;
    }
    T1 first;
    T2 second;
};


}
#endif