#include "../datastructs/Matrix.hpp"
#include <gtest/gtest.h>

TEST(MatrixTest, DefaultConstructor) {
  Matrix m;
  EXPECT_EQ(m(0, 0), Complex());
  EXPECT_EQ(m(0, 1), Complex());
  EXPECT_EQ(m(1, 0), Complex());
  EXPECT_EQ(m(1, 1), Complex());
}

TEST(MatrixTest, ConstructorValues) {
  Matrix m(Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0));

  EXPECT_EQ(m(0, 0), Complex(1, 0));
  EXPECT_EQ(m(0, 1), Complex(2, 0));
  EXPECT_EQ(m(1, 0), Complex(3, 0));
  EXPECT_EQ(m(1, 1), Complex(4, 0));
}

TEST(MatrixTest, Identity) {
  Matrix I = Matrix::identity();

  EXPECT_EQ(I(0, 0), Complex(1, 0));
  EXPECT_EQ(I(1, 1), Complex(1, 0));
  EXPECT_EQ(I(0, 1), Complex(0, 0));
  EXPECT_EQ(I(1, 0), Complex(0, 0));
}

TEST(MatrixTest, Addition) {
  Matrix a(Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0));

  Matrix b(Complex(5, 0), Complex(6, 0), Complex(7, 0), Complex(8, 0));

  Matrix c = a + b;

  EXPECT_EQ(c(0, 0), Complex(6, 0));
  EXPECT_EQ(c(0, 1), Complex(8, 0));
  EXPECT_EQ(c(1, 0), Complex(10, 0));
  EXPECT_EQ(c(1, 1), Complex(12, 0));
}

TEST(MatrixTest, Subtraction) {
  Matrix a(Complex(5, 0), Complex(6, 0), Complex(7, 0), Complex(8, 0));

  Matrix b(Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0));

  Matrix c = a - b;

  EXPECT_EQ(c(0, 0), Complex(4, 0));
  EXPECT_EQ(c(0, 1), Complex(4, 0));
  EXPECT_EQ(c(1, 0), Complex(4, 0));
  EXPECT_EQ(c(1, 1), Complex(4, 0));
}

TEST(MatrixTest, Multiplication) {
  Matrix a(Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0));

  Matrix b(Complex(2, 0), Complex(0, 0), Complex(1, 0), Complex(2, 0));

  Matrix c = a * b;

  EXPECT_EQ(c(0, 0), Complex(4, 0));
  EXPECT_EQ(c(0, 1), Complex(4, 0));
  EXPECT_EQ(c(1, 0), Complex(10, 0));
  EXPECT_EQ(c(1, 1), Complex(8, 0));
}

TEST(MatrixTest, ScalarMultiplication) {
  Matrix a(Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0));

  Matrix c = a * Complex(2, 0);

  EXPECT_EQ(c(0, 0), Complex(2, 0));
  EXPECT_EQ(c(0, 1), Complex(4, 0));
  EXPECT_EQ(c(1, 0), Complex(6, 0));
  EXPECT_EQ(c(1, 1), Complex(8, 0));
}

TEST(MatrixTest, Determinant) {
  Matrix a(Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0));

  Complex det = a.determinant();
  EXPECT_EQ(det, Complex(-2, 0));
}

TEST(MatrixTest, Trace) {
  Matrix a(Complex(5, 0), Complex(2, 0), Complex(3, 0), Complex(7, 0));

  EXPECT_EQ(a.trace(), Complex(12, 0));
}

TEST(MatrixTest, Transpose) {
  Matrix a(Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0));

  Matrix t = a.transpose();

  EXPECT_EQ(t(0, 0), Complex(1, 0));
  EXPECT_EQ(t(0, 1), Complex(3, 0));
  EXPECT_EQ(t(1, 0), Complex(2, 0));
  EXPECT_EQ(t(1, 1), Complex(4, 0));
}

TEST(MatrixTest, Conjugate) {
  Matrix a(Complex(1, 1), Complex(2, -2), Complex(3, 3), Complex(4, -4));

  Matrix c = a.conjugate();

  EXPECT_EQ(c(0, 0), Complex(1, -1));
  EXPECT_EQ(c(0, 1), Complex(2, 2));
  EXPECT_EQ(c(1, 0), Complex(3, -3));
  EXPECT_EQ(c(1, 1), Complex(4, 4));
}

TEST(MatrixTest, Hermitian) {
  Matrix a(Complex(1, 1), Complex(2, 0), Complex(3, 0), Complex(4, -1));

  Matrix h = a.hermitian();

  EXPECT_EQ(h(0, 0), Complex(1, -1));
  EXPECT_EQ(h(0, 1), Complex(3, 0));
  EXPECT_EQ(h(1, 0), Complex(2, 0));
  EXPECT_EQ(h(1, 1), Complex(4, 1));
}

TEST(MatrixTest, Inverse) {
  Matrix a(Complex(4, 0), Complex(7, 0), Complex(2, 0), Complex(6, 0));

  Matrix inv = a.inverse();
  Matrix result = a * inv;

  Matrix I = Matrix::identity();

  EXPECT_NEAR(result(0, 0).get_real(), I(0, 0).get_real(), 1e-9);
  EXPECT_NEAR(result(1, 1).get_real(), I(1, 1).get_real(), 1e-9);
}

TEST(MatrixTest, Equality) {
  Matrix a(Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0));

  Matrix b(Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0));

  Matrix c = Matrix::identity();

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
}
