#include "../datastructs/Stack.hpp"
#include <gtest/gtest.h>

TEST(StackTest, PushPopPeek) {
  Stack<int> s;
  EXPECT_TRUE(s.empty());
  s.push(1);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.peek(), 1);
  s.push(2);
  EXPECT_EQ(s.peek(), 2);
  s.pop();
  EXPECT_EQ(s.peek(), 1);
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, PopEmptyThrows) {
  Stack<int> s;
  EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(StackTest, PeekEmptyThrows) {
  Stack<int> s;
  EXPECT_THROW(s.peek(), std::out_of_range);
}

TEST(StackTest, ConstPeek) {
  Stack<int> s;
  s.push(42);
  const Stack<int> &cs = s;
  EXPECT_EQ(cs.peek(), 42);
}

TEST(StackTest, LIFOOrder) {
  Stack<int> s;
  for (int i = 0; i < 5; i++)
    s.push(i);
  for (int i = 4; i >= 0; i--) {
    EXPECT_EQ(s.peek(), i);
    s.pop();
  }
  EXPECT_TRUE(s.empty());
}
