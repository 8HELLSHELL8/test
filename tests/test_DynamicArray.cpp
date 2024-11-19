#include <gtest/gtest.h>
#include "/home/anton/3laba_2kurs/src/DynamicArray.h"

TEST(DynamicArray_test, defaultConstructor)
{
    DynamicArray<string> myArray;
    EXPECT_EQ(myArray.size(), 0);
    EXPECT_EQ(myArray.memory_use(), 1);
}

TEST(DynamicArray_test, initializerConstructor)
{
    DynamicArray<int> myArray{1, 2, 3};
    EXPECT_EQ(myArray.size(), 3);
    EXPECT_EQ(myArray.MGET(0), 1);
    EXPECT_EQ(myArray.MGET(1), 2);
    EXPECT_EQ(myArray.MGET(2), 3);
}

TEST(DynamicArray_test, copyConstructor)
{
    DynamicArray<int> initial{1, 2, 3, 4, 5};
    DynamicArray<int> myArray = initial;
    EXPECT_EQ(myArray.size(), initial.size());
    EXPECT_EQ(myArray.MGET(0), initial.MGET(0));
    EXPECT_EQ(myArray.MGET(1), initial.MGET(1));
    EXPECT_EQ(myArray.MGET(2), initial.MGET(2));
    EXPECT_EQ(myArray.MGET(3), initial.MGET(3));
    EXPECT_EQ(myArray.MGET(4), initial.MGET(4));
}

TEST(DynamicArray_test, assigmentOperator)
{
    DynamicArray<int> initial{1, 2, 3, 4, 5};
    DynamicArray<int> myArray;
    myArray = initial;
    EXPECT_EQ(myArray.size(), initial.size());
    EXPECT_EQ(myArray.MGET(0), initial.MGET(0));
    EXPECT_EQ(myArray.MGET(1), initial.MGET(1));
    EXPECT_EQ(myArray.MGET(2), initial.MGET(2));
    EXPECT_EQ(myArray.MGET(3), initial.MGET(3));
    EXPECT_EQ(myArray.MGET(4), initial.MGET(4));
}

TEST(DynamicArray_test, MPUSH)
{
    DynamicArray<int> initial;
    initial.MPUSH(1);
    initial.MPUSH(2);
    initial.MPUSH(3);
    EXPECT_EQ(initial.MGET(0), 1);
    EXPECT_EQ(initial.MGET(1), 2);
    EXPECT_EQ(initial.MGET(2), 3);
    EXPECT_EQ(initial.size(), 3);
}

TEST(DynamicArray_test, MPUSHAtIndex)
{
    DynamicArray<int> array{20, 40, 60};
    array.MPUSH(10, 0);
    EXPECT_EQ(array.MGET(0), 10);
    EXPECT_EQ(array.MGET(1), 20);

    array.MPUSH(30, 2);
    EXPECT_EQ(array.MGET(2), 30);
    EXPECT_EQ(array.MGET(3), 40);

    array.MPUSH(50, 4);
    EXPECT_EQ(array.MGET(4), 50);
    EXPECT_EQ(array.MGET(5), 60);
    EXPECT_EQ(array.size(), 6);

}

TEST(DynamicArrayTest, Iterators) 
{
    DynamicArray<int> array = {10, 20, 30};
    auto it = array.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(it, array.end());
}



TEST(DynamicArray_test, MDEL)
{
    DynamicArray<int> array{10,100,1000};

    array.MDEL(1);
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.MGET(0), 10);
    EXPECT_EQ(array.MGET(1), 1000);

    array.MDEL(1);
    array.MDEL(0);
    EXPECT_EQ(array.size(), 0);
    
    try
    {
        array.MDEL(0);
    }
    catch(const out_of_range& e)
    {
        EXPECT_STREQ(e.what(), "Index out of range");
    }
}

TEST(DynamicArray_test, MSET)
{
    DynamicArray<int> array{1,2,3};
    array.MSET(10,0);
    EXPECT_EQ(array.MGET(0), 10);

    array.MSET(20,1);
    EXPECT_EQ(array.MGET(1), 20);

    array.MSET(30,2);
    EXPECT_EQ(array.MGET(2), 30);
    EXPECT_EQ(array.size(), 3);
}

TEST(DynamicArrayTest, Resize) 
{
    DynamicArray<int> array;
    array.MPUSH(10);
    array.resize(5);
    EXPECT_EQ(array.memory_use(), 5);
    EXPECT_EQ(array.size(), 1);
}
