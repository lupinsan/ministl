#include"../src/functions/m_functor.h"
#include "../src/mini_iterator/mini_iter.h"
#include "../src/mini_memory/mini_memory.h"
#include "../src/algorithm/m_algo.h"
#include "../src/hashtable/m_hashtable.h"
#include <iostream>
#include <gtest/gtest.h>



int main(){
    mini::hashtable<int,int,mini::hash<int>,mini::identity<int>,mini::equal_to<int>,__malloc_alloc>
        iht(50,mini::hash<int>(),mini::equal_to<int>());
    
    std::cout<<iht.size()<<'\n';
    std::cout<<iht.bucket_count()<<'\n';
    std::cout<<iht.max_buck_count()<<'\n';

    iht.insert_unique(59);
    iht.insert_unique(63);
    iht.insert_unique(108);
    iht.insert_unique(2);
    iht.insert_unique(53);
    iht.insert_unique(55);
    iht.insert_equal(55);
    std::cout<<iht.size()<<'\n';

    mini::hashtable<int,int,mini::hash<int>,mini::identity<int>,mini::equal_to<int>,__malloc_alloc>
    ::iterator ite =iht.begin();

    for(int i=0;i<iht.size();++i,++ite){
        std::cout<<*ite<<' ';
    }
    std::cout<<'\n';

    // for(int i=0;i<iht.bucket_count();++i){
    //     int n=iht.elems_in_bucket(i);
    //     if(n!=0)
    //         std::cout<<"bucket["<<i<<"]has"<<n<<" elems"<<'\n';
    // }

    std::cout<<iht.count(55)<<'\n';
}
