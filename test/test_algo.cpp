#include "../src/mini_iterator/mini_iter.h"
#include "../src/mini_memory/mini_memory.h"
#include "../src/algorithm/m_algo.h"
#include "../src/vector/m_vector.h"
#include <iostream>
#include <gtest/gtest.h>

int main(){
    mini::vector<int> a;//实现花括号列表初始化？
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(4);

    mini::vector<int> b;
    b.push_back(3);
    b.push_back(4);


    // auto k = mini::adjacent_find(a.begin(),a.end());
    // std::cout<<*(k)<<'\n';

    // auto k = mini::count(a.begin(),a.end(),4);
    // std::cout<<k<<'\n';

    // auto k = mini::count_if(a.begin(),a.end(),[](auto a){return a==4;});
    // std::cout<<k<<'\n';

    // auto k =mini::find(a.begin(),a.end(),3);
    // std::cout<<*k<<'\n';

    // auto k = mini::for_each(a.begin(),a.end(),[](auto& a){a=a+1;return;});
    // std::cout<<a[0]<<'\n';

    // auto sb = mini::includes(a.begin(),a.end(),b.begin(),b.end());
    // std::cout<<sb<<'\n';

    // auto sb = mini::includes(a.begin(),a.end(),b.begin(),b.end(),[](auto a, auto b){return a==b;});
    // std::cout<<sb<<'\n';

    // auto sb = mini::max_element(a.begin(),a.end());
    // std::cout<<*sb<<'\n';

    // auto sb = mini::max_element(a.begin(),a.end(),[](auto a, auto b){return a<b;});
    // std::cout<<*sb;

    



    return 0;
}