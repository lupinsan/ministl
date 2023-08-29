#include "../src/mini_iterator/mini_iter.h"
#include "../src/mini_memory/mini_memory.h"
#include "../src/algorithm/m_algo.h"
#include "../src/queue/m_queue.h"
#include "../src/stack/m_stack.h"
#include <iostream>
#include <gtest/gtest.h>

int main(){

    mini::stack<int> s1;
    s1.push(3);
    EXPECT_EQ(s1.top(),3);
    s1.push(4);
    EXPECT_EQ(s1.top(),4);

    // mini::stack<int> s2(s1);
    // EXPECT_EQ(s2.top(),4);

    // mini::stack<int> s2(std::move(s1));
    // EXPECT_EQ(s2.top(),4);

    // mini::stack<int> s2=std::move(s1);
    // EXPECT_EQ(s2.top(),4);

    mini::queue<int> q1;
    q1.push(3);
    EXPECT_EQ(q1.front(),3);
    q1.push(4);
    EXPECT_EQ(q1.front(),3);

    // mini::queue<int> q2(q1);
    // EXPECT_EQ(q2.front(),3);

    mini::queue<int> q2(std::move(q1));
    EXPECT_EQ(q2.front(),3);

    // mini::queue<int> q2=std::move(q1);
    // EXPECT_EQ(q2.front(),3);
}