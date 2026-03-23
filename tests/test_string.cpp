#include "../datastructs/String.hpp"
#include <cstring>
#include <gtest/gtest.h>

TEST(String, Constructor) {
  String s("hello");
  EXPECT_EQ(s.size(), 5);
  EXPECT_STREQ(s.c_str(), "hello");
}

TEST(String, CopyConstructor) {
  String a("test");
  String b = a;

  EXPECT_STREQ(b.c_str(), "test");
}

TEST(String, Assignment) {
  String a("one");
  String b("two");

  b = a;
  EXPECT_STREQ(b.c_str(), "one");
}

TEST(String, Indexing) {
  String s("abc");

  EXPECT_EQ(s[0], 'a');
  s[1] = 'z';
  EXPECT_EQ(s[1], 'z');
}
