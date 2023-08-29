#include"../src/functions/m_functor.h"
#include "../src/mini_iterator/mini_iter.h"
#include "../src/mini_memory/mini_memory.h"
#include "../src/algorithm/m_algo.h"
// #include "../src/unordered_set/m_unordered_set.h"
// #include "../src/unordered_set/m_unordered_map.h"
// #include "../src/unordered_set/hash_mutiset.h"
#include "../src/unordered_set/hash_mutimap.h"

#include <iostream>
#include <gtest/gtest.h>
#include <cstring>
using namespace std;

struct eqstr{
    bool operator()(const char* s1,const char* s2) const{
        return strcmp(s1,s2)==0;
    }
};


int main(){
    //unordered_set
    // mini::hash_set<const char*, hash<const char*>,eqstr> Set;
    // Set.insert("kiwi");
    // Set.insert("plum");
    // Set.insert("apple");
    // Set.insert("mango");
    // Set.insert("apricot");
    // Set.insert("banana");
    // mini::hash_set<const char*,hash<const char*>,eqstr>::iterator ite1=Set.begin();
    // mini::hash_set<const char*,hash<const char*>,eqstr>::iterator ite2;

    // for(int i=0;i<Set.size();++i,++ite1){
    //     cout<<*ite1<<' ';
    // }
    // cout<<'\n';

    // mini::hash_set<int> Set1;
    // Set1.insert(59);
    // Set1.insert(63);
    // Set1.insert(108);
    // Set1.insert(2);
    // Set1.insert(53);
    // Set1.insert(55);

    // mini::hash_set<int>::iterator ite3 = Set1.begin();
    // for(int i=0;i<Set1.size();++i,++ite3){
    //     cout<<*ite3<<' ';
    // }
    // cout<<'\n';


    //unordered_map
    // mini::hash_map<char*,int,hash<char*>, eqstr> days;

    // days["january"] = 31;
    // days["february"] = 28;
    // days["march"] = 31;
    // days["april"] = 30;
    // days["may"] = 31;
    // days["june"] = 30;
    // days["july"] = 31;
    
    // mini::hash_map<char*,int,hash<char*>, eqstr> ::iterator ite1 =days.begin();


    // for(int i=0;i<days.size();++i,++ite1){
    //     cout<<ite1->second<<' ';
    // }
    // cout<<'\n';


    //hash_mutiset
    // mini::hash_multiset<int> mset;
    // mset.insert(1);
    // mset.insert(2);
    // mset.insert(3);
    // mset.insert(4);
    // mset.insert(4);

    // mini::hash_multiset<int>::iterator ite1=mset.begin();
    // for(int i=0;i<mset.size();++i,++ite1){
    //     cout<<*ite1<<' ';
    // }
    // cout<<'\n';


    //hash_mutimap
    // mini::hash_mutimap<char*,int,hash<char*>,eqstr> mmap;











}