#include"../src/functions/m_functor.h"
#include "../src/mini_iterator/mini_iter.h"
#include "../src/mini_memory/mini_memory.h"
#include "../src/algorithm/m_algo.h"
#include "../src/RB-tree/m_rb_tree.h"
#include <iostream>
#include <gtest/gtest.h>

int main(){
    mini::rb_tree<int,int,mini::identity<int>,mini::less<int>> itree;
    itree.insert_unique(10);
    itree.insert_unique(7);
    itree.insert_unique(8);
    itree.insert_unique(15);
    itree.insert_unique(5);
    itree.insert_unique(6);
    itree.insert_unique(11);
    itree.insert_unique(13);
    itree.insert_unique(12);

    std::cout<<itree.size()<<'\n';
    
    mini::rb_tree<int,int,mini::identity<int>,mini::less<int>>::iterator ite1 = itree.begin();
    mini::rb_tree<int,int,mini::identity<int>,mini::less<int>>::iterator ite2 = itree.end();

    for(;ite1 != ite2;++ite1){
        mini::__rb_tree_base_iterator rbtite = mini::__rb_tree_base_iterator(ite1);
        std::cout<<*ite1<<'('<<ite1.node->color<<") ";
    }
    std::cout<<'\n';

    // ite1 = itree.find(5);
    // std::cout<<*ite1<<'\n';

    //shanchu


    //3456
    // std::cout<<(itree.header->right)<<'\n';
    // ite1 = itree.find(13);
    // itree.erase(ite1); 

    // ite1 = itree.find(15);
    // std::cout<<(itree.header->right)<<'\n';
    // itree.erase(ite1); 

    // std::cout<<itree.value((itree.header->right))<<'\n';


    //2:1

    // ite1 = itree.find(10);
    // std::cout<<(itree.header->right)<<'\n';
    // itree.erase(ite1); 


    //2:2
    // ite1 = itree.find(15);
    // std::cout<<(itree.header->right)<<'\n';
    // itree.erase(ite1); 
    // ite1 = itree.find(10);
    // std::cout<<(itree.header->right)<<'\n';
    // itree.erase(ite1); 

    //2:3
    // ite1 = itree.find(12);
    // std::cout<<(itree.header->right)<<'\n';
    // itree.erase(ite1); 
    // ite1 = itree.find(15);
    // std::cout<<(itree.header->right)<<'\n';
    // itree.erase(ite1); 
    // ite1 = itree.find(10);
    // std::cout<<(itree.header->right)<<'\n';
    // itree.erase(ite1); 

    itree.clear();


    std::cout<<'\n';
    std::cout<<"begin:"<<*itree.begin()<<'\n';
    std::cout<<"end:"<<(itree.rightmost()->value_field)<<'\n';
    std::cout<<itree.size()<<'\n';



}
