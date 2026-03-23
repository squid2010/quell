#include <gtest/gtest.h>
#include "../datastructs/Complex.hpp"

TEST(Complex, Constructors) {
    Complex c1;
    EXPECT_DOUBLE_EQ(c1.get_real(), 0.0);
    EXPECT_DOUBLE_EQ(c1.get_imag(), 0.0);

    Complex c2(3.0, 4.0);
    EXPECT_DOUBLE_EQ(c2.get_real(), 3.0);
    EXPECT_DOUBLE_EQ(c2.get_imag(), 4.0);
}

TEST(Complex, Arithmetic) {
    Complex a(1, 2);
    Complex b(3, 4);

    Complex sum = a + b;
    EXPECT_DOUBLE_EQ(sum.get_real(), 4);
    EXPECT_DOUBLE_EQ(sum.get_imag(), 6);

    Complex diff = a - b;
    EXPECT_DOUBLE_EQ(diff.get_real(), -2);
    EXPECT_DOUBLE_EQ(diff.get_imag(), -2);

    Complex prod = a * b;
    EXPECT_DOUBLE_EQ(prod.get_real(), -5);
    EXPECT_DOUBLE_EQ(prod.get_imag(), 10);
}

TEST(Complex, Division) {
    Complex a(1, 2);
    Complex b(3, 4);

    Complex result = a / b;

    EXPECT_NEAR(result.get_real(), 0.44, 1e-2);
    EXPECT_NEAR(result.get_imag(), 0.08, 1e-2);
}

TEST(Complex, Scalar) {
    Complex a(2, 3);
    Complex b = a * 2;

    EXPECT_DOUBLE_EQ(b.get_real(), 4);
    EXPECT_DOUBLE_EQ(b.get_imag(), 6);
}

TEST(Complex, Math) {
    Complex a(3, 4);

    EXPECT_DOUBLE_EQ(a.norm(), 25);
    EXPECT_DOUBLE_EQ(a.abs(), 5);

    Complex c = a.conj();
    EXPECT_DOUBLE_EQ(c.get_real(), 3);
    EXPECT_DOUBLE_EQ(c.get_imag(), -4);
}
