#include <gtest/gtest.h>
#include "/home/anton/3laba_2kurs/src/ForwardList.h"

TEST(ForwardList_test, defaultConstructor)
{
    ForwardList list;
    EXPECT_EQ(list.size(), 0);
}

TEST(ForwardList_test, isEmpty)
{
    ForwardList list;
    EXPECT_EQ(list.is_empty(), 1);
    list.addtail("element");
    EXPECT_EQ(list.is_empty(), 0);
}

TEST(ForwardList_test, size)
{
    ForwardList list;
    EXPECT_EQ(list.size(), 0);
    list.addtail("kek");
    EXPECT_EQ(list.size(), 1);
}

TEST(ForwardList_test, addTail)
{
    ForwardList list;
    list.addtail("check");
    EXPECT_EQ(list.size(), 1);
    list.addtail("newword");
    EXPECT_EQ(list.get(0), "check");
    EXPECT_EQ(list.get(1), "newword");
    EXPECT_EQ(list.size(), 2);
}