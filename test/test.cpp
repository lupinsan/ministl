#include "../src/mini_iterator/mini_iter.h"
#include "../src/mini_memory/mini_memory.h"
#include "../src/algorithm/m_algo.h"
#include "../src/vector/m_vector.h"
#include <iostream>
#include <gtest/gtest.h>
#include "../src/list/m_list.h"


class A{
public:
    int* p;
    char a;
    A():a('3'){
        p = new int();
        std::cout<<"A's constructer is called!\n";
    }
    ~A(){
        free(p);
        std::cout<<"A's destroy func is called!\n";
    }
};


int main()
{
    // simple_alloc<int> A1;
    // int* p1 = A1.allocate(4);
    
    // uninitialized_fill_n(p1,4,3);
    // *p1=1;
    // *(p1+1)=2;
    // *(p1+2)=3;
    // *(p1+3)=4;
    // *(p1+4)=5;
    // *(p1+5)=6;


    // int* p2 = A1.allocate(6);
    // uninitialized_fill_n(p2,4,2);
    // copy_backward(p1+5,p1,p1+1);

    // for(int i=0;i<6;++i){
    //     std::cout<<*(p1+i)<<'\n';
    // }

    // A1.deallocate(p1);
    // A1.deallocate(p2);


    //test vector

    mini::vector<int> v1;//(10,10);
    // for(int i=0;i<10;++i){
    //    std::cout<<v1[i]<<'\n';
    //         v1[i]=i+1;
    // }
    v1.push_back(3);
    for(int i=0;i<2;++i){
       std::cout<<v1[i]<<'\n';
    }

//     EXPECT_EQ(1,v1.front());
//     EXPECT_EQ(10,v1.back());

//     v1.push_back(11);
//     EXPECT_EQ(11,v1.back());
//     EXPECT_EQ(20,v1.__tatol());

//     v1.pop_back();
//     EXPECT_EQ(10,v1.back());
    
//     EXPECT_EQ(5,v1[4]);
//     //v1.erase(&v1[0]+4);

//     v1.erase(v1.begin()+4,v1.begin()+6);
//     EXPECT_EQ(7,v1[4]);

//     v1.insert(v1.begin()+4,1,8);
//     EXPECT_EQ(8,v1[4]);


    //list basic functions test

    // mini::list<int> l2;
    // l2.push_back(1);
    // l2.push_back(2);
    // l2.push_back(3);

    // EXPECT_EQ(*l2.begin(),1);
    // l2.pop_front();
    // EXPECT_EQ(*l2.begin(),2);
    // l2.pop_back();
    // EXPECT_EQ(*(--l2.end()),2);

    // l2.insert(l2.end(),5);
    // EXPECT_EQ(*(--l2.end()),5);

    // l2.insert(l2.begin(),1);
    // for(mini::list<int>::iterator i=l2.begin();i!=l2.end();++i){
    //     std::cout<<*i<<'\n';
    // }

    // l2.pop_back();
    // EXPECT_EQ(*(--l2.end()),2);
    // l2.pop_front();
    // EXPECT_EQ(*l2.begin(),2);

    // l2.insert(l2.end(),6);
    // l2.insert(l2.end(),7);
    // l2.insert(l2.end(),8);
    // l2.unique();
    // mini::list<int>::iterator j=l2.begin();

    // for(mini::list<int>::iterator i=l2.begin();i!=l2.end();++i){
    //     std::cout<<*i<<'\n';
    // }

    // l2.reverse();
    // for(mini::list<int>::iterator i=l2.begin();i!=l2.end();++i){
    //     std::cout<<*i<<'\n';
    // }
    // l2.reverse();

    
    // i++;
    // i++;

    // l2.splice(++(l2.begin()),l2,i,l2.end());

    // for(mini::list<int>::iterator i=l2.begin();i!=l2.end();++i){
    //     std::cout<<*i<<'\n';
    // }

    
    // mini::list<int> l3;
    // l3.insert(l3.end(),1);
    // l3.insert(l3.end(),2);
    // l3.insert(l3.end(),3);

    // l2.merge(l3);

    // for(mini::list<int>::iterator i=l2.begin();i!=l2.end();++i){
    //     std::cout<<*i<<'\n';
    // }

    







    return 0;

}



