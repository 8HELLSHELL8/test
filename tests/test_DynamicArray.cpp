#include <gtest/gtest.h>
#include "/home/anton/3laba_2kurs/src/DynamicArray.h"

TEST(DynamicArray_test, defaultConstructor)
{
    DynamicArray<string> myArray;
    EXPECT_EQ(myArray.size(), 0);
}

TEST(DynamicArray_test, initializerConstructor)
{
    DynamicArray<string> myArray{"1","1","1"};
    EXPECT_EQ(myArray.size(), 3);
}

TEST(DynamicArray_test, copyConstructor)
{
    DynamicArray<string> initial{"1","1","1","1","1"};
    DynamicArray<string> myArray = initial;
    EXPECT_EQ(myArray, initial);
}

