#include "../datastructs/DynamicArray.hpp"
#include <gtest/gtest.h>

TEST(DynamicArray, PushBackAndSize) {
  DynamicArray<int> arr;

  arr.push_back(10);
  arr.push_back(20);

  EXPECT_EQ(arr.get_size(), 2);
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[1], 20);
}

TEST(DynamicArray, PopBack) {
  DynamicArray<int> arr;

  arr.push_back(1);
  arr.push_back(2);
  arr.pop_back();

  EXPECT_EQ(arr.get_size(), 1);
  EXPECT_EQ(arr[0], 1);
}

TEST(DynamicArray, CopyConstructor) {
  DynamicArray<int> a;
  a.push_back(5);

  DynamicArray<int> b = a;

  EXPECT_EQ(b.get_size(), 1);
  EXPECT_EQ(b[0], 5);
}

TEST(DynamicArray, Assignment) {
  DynamicArray<int> a;
  a.push_back(7);

  DynamicArray<int> b;
  b = a;

  EXPECT_EQ(b.get_size(), 1);
  EXPECT_EQ(b[0], 7);
}
