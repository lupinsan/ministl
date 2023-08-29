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


int main(){

    // mini::vector<int> v1(4,1);
    // mini::vector<int> v2(v1);
    // v1.push_back(5);
    // EXPECT_EQ(4,v2.size());
    // EXPECT_EQ(5,v1.size());
    
    // v2=v1;
    // EXPECT_EQ(v2[4],5);
    // v2=std::move(v1);
    // EXPECT_EQ(v1.size(),0);
    // mini::vector<int> v3(std::move(v2));

    // EXPECT_EQ(v2.size(),0);
    // EXPECT_EQ(v3[4],5);


    mini::list<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);

    mini::list<int> l2(l1);
    mini::list<int>::iterator beg = l2.begin();

    for(beg = l2.begin();beg!=l2.end();++beg){
        std::cout<<*beg<<'\n';
    }
    // l1.pop_back();
    // l1.pop_back();
    // EXPECT_EQ(l1.size(),2);
    // for(beg = l2.begin();beg!=l2.end();++beg){
    //     std::cout<<*beg<<'\n';
    // }

    mini::list<int> l3;
    l3=l1;
    EXPECT_EQ(*l3.begin(),1);

    l3=std::move(l1);
    EXPECT_EQ(l1.size(),0);

    mini::list<int> l4(std::move(l3));
    EXPECT_EQ(*l4.begin(),1);
    EXPECT_EQ(l3.size(),0);

    mini::list<int> l5;
    l5.push_back(5);
    l5.push_back(6);
    l5.push_back(7);
    l5.push_back(8);

    l1.swap(l5);
    for(beg = l1.begin();beg!=l1.end();++beg){
        std::cout<<*beg<<'\n';
    }
    for(beg = l5.begin();beg!=l5.end();++beg){
        std::cout<<*beg<<'\n';
    }
    // for(beg = l4.begin();beg!=l4.end();++beg){
    //     std::cout<<*beg<<'\n';
    // }




}
