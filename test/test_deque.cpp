#include "../src/mini_iterator/mini_iter.h"
#include "../src/mini_memory/mini_memory.h"
#include "../src/algorithm/m_algo.h"
#include "../src/deque/m_deque.h"
#include <iostream>
#include <gtest/gtest.h>


int main(){
    
    mini::deque<int,__malloc_alloc,0> d1;
    //EXPECT_EQ(d1[1],1);
    // std::cout<<"map:"<<d1.__map_size()<<'\n';
    // std::cout<<"size:"<<d1.size()<<'\n';


    d1.push_back(5);
    EXPECT_EQ(d1.back(),5);
    d1.push_front(6);
    EXPECT_EQ(d1.front(),6);

    //d1.clear();


    // for(int i=0;i<d1.size();++i){
    //     std::cout<<d1[i]<<'\n';
    // }

    // auto d2(d1);
    // for(int i=0;i<d2.size();++i){
    //     std::cout<<d2[i]<<'\n';
    // }

    //mini::deque<int>d3(std::move(d1));
    mini::deque<int>d3 = std::move(d1);



    // d3.push_back(3);
    // d3.push_front(3);

    // d3 = d1;
    // EXPECT_EQ(d3[0],6);

    for(int i=0;i<d3.size();++i){
        std::cout<<d3[i]<<'\n';
    }




    // std::cout<<'\n';
    // mini::deque<int>::iterator p = d1.end();
    // mini::deque<int>::iterator p1 = d1.begin();
    
    // mini::deque<int> d2(3,2);
    // auto beg2 = d2.begin();

    // d2.insert(p1,p,beg2);

    // for(int i=0;i<d2.size();++i){
    //     std::cout<<d2[i]<<'\n';
    // }
    // d1.erase(p,p1);

    // d1.insert(p,3);

    // for(int i=0;i<d1.size();++i){
    //     std::cout<<d1[i]<<'\n';
    // }








    //容量以及其延展性测试
    //pop后其实际占有空间被dealloc但是map**指表中空间仍然存在，这只占一小部分没有大影响
    // std::cout<<"map:"<<d1.__map_size()<<'\n';
    // std::cout<<"size:"<<d1.size()<<'\n';

    // for(int i=0;i<3000;++i){
    //     d1.push_back(i);
    //     //std::cout<<d1.back()<<'\n';
    // }

    // std::cout<<"map:"<<d1.__map_size()<<'\n';
    // std::cout<<"size:"<<d1.size()<<'\n';
    // for(int i=0;i<3000;++i){
    //     d1.pop_back();
    // }
    // std::cout<<"map:"<<d1.__map_size()<<'\n';
    // std::cout<<"size:"<<d1.size()<<'\n';


    


    // for(int i=0;i<3000;++i){
    //     d1.push_front(i);
    //     //std::cout<<d1.front()<<'\n';
    // }

    // std::cout<<"map:"<<d1.__map_size()<<'\n';
    // std::cout<<"size:"<<d1.size()<<'\n';


    // for(int i=0;i<3000;++i){
    //     d1.pop_front();
    // }

    // std::cout<<"map:"<<d1.__map_size()<<'\n';
    // std::cout<<"size:"<<d1.size()<<'\n';







}