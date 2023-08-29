#include "../src/mini_iterator/mini_iter.h"
#include "../src/mini_memory/mini_memory.h"
#include "../src/algorithm/m_algo.h"
#include "../src/set/m_set.h"
#include <iostream>
#include <gtest/gtest.h>

int main(){
    mini::set<int> s1;
    s1.insert(3);
    s1.insert(4);
    s1.insert(1);
    for(auto x = s1.begin();x!=s1.end();++x){
        std::cout<<*x<<'\n';
    }
    auto x1 =s1.begin();
    // s1.erase(x1);
    s1.erase(1);
    for(auto x = s1.begin();x!=s1.end();++x){
        std::cout<<*x<<'\n';
    }

    





}