#include "../datastructs/DynamicArray.hpp"
#include <gtest/gtest.h>

TEST(DynamicArrayTest, PushAndAccess) {
  DynamicArray<int> arr;
  arr.push_back(10);
  arr.push_back(20);

  EXPECT_EQ(arr.get_size(), 2);
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[1], 20);
}

TEST(DynamicArrayTest, PopBack) {
  DynamicArray<int> arr;
  arr.push_back(5);
  arr.push_back(15);

  arr.pop_back();
  EXPECT_EQ(arr.get_size(), 1);
  EXPECT_EQ(arr[0], 5);
}

TEST(DynamicArrayTest, CopyConstructor) {
  DynamicArray<int> arr1;
  arr1.push_back(1);
  arr1.push_back(2);

  DynamicArray<int> arr2 = arr1;
  EXPECT_EQ(arr2.get_size(), 2);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
}

TEST(DynamicArrayTest, CopyAssignment) {
  DynamicArray<int> arr1;
  arr1.push_back(3);
  arr1.push_back(4);

  DynamicArray<int> arr2;
  arr2 = arr1;

  EXPECT_EQ(arr2.get_size(), 2);
  EXPECT_EQ(arr2[0], 3);
  EXPECT_EQ(arr2[1], 4);
}

TEST(DynamicArrayTest, MoveConstructor) {
  DynamicArray<int> arr1;
  arr1.push_back(1);
  arr1.push_back(2);

  DynamicArray<int> arr2 = std::move(arr1);
  EXPECT_EQ(arr2.get_size(), 2);
}

TEST(DynamicArrayTest, MoveAssignment) {
  DynamicArray<int> arr1;
  arr1.push_back(5);

  DynamicArray<int> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.get_size(), 1);
}
