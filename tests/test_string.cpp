#include "../datastructs/String.hpp"
#include <gtest/gtest.h>

TEST(StringTest, DefaultConstructor) {
  String s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_STREQ(s.c_str(), "");
}

TEST(StringTest, ConstructorFromCStr) {
  String s("hello");
  EXPECT_EQ(s.size(), 5);
  EXPECT_STREQ(s.c_str(), "hello");
}

TEST(StringTest, CopyConstructor) {
  String s1("test");
  String s2(s1);
  EXPECT_EQ(s2.size(), 4);
  EXPECT_STREQ(s2.c_str(), "test");
}

TEST(StringTest, AssignmentOperator) {
  String s1("foo");
  String s2;
  s2 = s1;
  EXPECT_EQ(s2.size(), 3);
  EXPECT_STREQ(s2.c_str(), "foo");
}

TEST(StringTest, AccessOperators) {
  String s("abc");
  s[0] = 'x';
  EXPECT_EQ(s[0], 'x');
  EXPECT_EQ(s[1], 'b');
  EXPECT_EQ(s[2], 'c');

  const String cs("xyz");
  EXPECT_EQ(cs[0], 'x');
  EXPECT_EQ(cs[1], 'y');
  EXPECT_EQ(cs[2], 'z');
}
