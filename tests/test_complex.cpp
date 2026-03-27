#include "../datastructs/Complex.hpp"
#include <cmath>
#include <gtest/gtest.h>

TEST(ComplexTest, DefaultConstructor) {
  Complex c;
  EXPECT_DOUBLE_EQ(c.get_real(), 0.0);
  EXPECT_DOUBLE_EQ(c.get_imag(), 0.0);
}

TEST(ComplexTest, ConstructorValues) {
  Complex c(3.0, 4.0);
  EXPECT_DOUBLE_EQ(c.get_real(), 3.0);
  EXPECT_DOUBLE_EQ(c.get_imag(), 4.0);
}

TEST(ComplexTest, Addition) {
  Complex a(1, 2), b(3, 4);
  Complex c = a + b;
  EXPECT_DOUBLE_EQ(c.get_real(), 4);
  EXPECT_DOUBLE_EQ(c.get_imag(), 6);
}

TEST(ComplexTest, Subtraction) {
  Complex a(5, 6), b(2, 3);
  Complex c = a - b;
  EXPECT_DOUBLE_EQ(c.get_real(), 3);
  EXPECT_DOUBLE_EQ(c.get_imag(), 3);
}

TEST(ComplexTest, Multiplication) {
  Complex a(1, 2), b(3, 4);
  Complex c = a * b;
  EXPECT_DOUBLE_EQ(c.get_real(), -5);
  EXPECT_DOUBLE_EQ(c.get_imag(), 10);
}

TEST(ComplexTest, Division) {
  Complex a(1, 2), b(1, 1);
  Complex c = a / b;
  EXPECT_NEAR(c.get_real(), 1.5, 1e-9);
  EXPECT_NEAR(c.get_imag(), 0.5, 1e-9);
}

TEST(ComplexTest, ScalarMultiplication) {
  Complex a(2, 3);
  Complex c = a * 2;
  EXPECT_DOUBLE_EQ(c.get_real(), 4);
  EXPECT_DOUBLE_EQ(c.get_imag(), 6);
}

TEST(ComplexTest, CompoundOperators) {
  Complex a(1, 2), b(3, 4);
  a += b;
  EXPECT_DOUBLE_EQ(a.get_real(), 4);
  EXPECT_DOUBLE_EQ(a.get_imag(), 6);

  a -= b;
  EXPECT_DOUBLE_EQ(a.get_real(), 1);
  EXPECT_DOUBLE_EQ(a.get_imag(), 2);

  a *= b;
  EXPECT_DOUBLE_EQ(a.get_real(), -5);
  EXPECT_DOUBLE_EQ(a.get_imag(), 10);

  a /= b;
  EXPECT_NEAR(a.get_real(), 1, 1e-9);
  EXPECT_NEAR(a.get_imag(), 2, 1e-9);

  a *= 2;
  EXPECT_DOUBLE_EQ(a.get_real(), 2);
  EXPECT_DOUBLE_EQ(a.get_imag(), 4);
}

TEST(ComplexTest, Comparisons) {
  Complex a(1, 2), b(1, 2), c(2, 3);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
}

TEST(ComplexTest, MathFunctions) {
  Complex a(3, 4);
  EXPECT_DOUBLE_EQ(a.norm(), 25);
  EXPECT_DOUBLE_EQ(a.abs(), 5);
  EXPECT_DOUBLE_EQ(a.arg(), std::atan2(4, 3));
  Complex conj = a.conj();
  EXPECT_DOUBLE_EQ(conj.get_real(), 3);
  EXPECT_DOUBLE_EQ(conj.get_imag(), -4);
}
