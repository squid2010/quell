#include "Complex.hpp"
#include <cmath>

// Constructors

Complex::Complex() {
  real = 0.0;
  imaginary = 0.0;
}

Complex::Complex(double real, double imaginary) { // Constructor from a value
  this->real = real;
  this->imaginary = imaginary;
}

// Arithmetic
Complex Complex::operator+(const Complex &other) const { // addition
  return Complex(real + other.real, imaginary + other.imaginary);
}

Complex Complex::operator-(const Complex &other) const { // subtraction
  return Complex(real - other.real, imaginary - other.imaginary);
}

Complex Complex::operator*(const Complex &other) const { // multiplication
  return Complex(real * other.real - imaginary * other.imaginary,
                 real * other.imaginary + imaginary * other.real);
}

Complex Complex::operator/(const Complex &other) const { // division
  double denom = other.real * other.real + other.imaginary * other.imaginary;

  double r = (real * other.real + imaginary * other.imaginary) / denom;
  double i = (imaginary * other.real - real * other.imaginary) / denom;

  return Complex(r, i);
}

Complex Complex::operator*(const double scalar) const { // scalar multiplication
  return Complex(real * scalar, imaginary * scalar);
}

// Compound operators
void Complex::operator+=(const Complex &other) { // +=
  real += other.real;
  imaginary += other.imaginary;
}

void Complex::operator-=(const Complex &other) { // -=
  real -= other.real;
  imaginary -= other.imaginary;
}

void Complex::operator*=(const Complex &other) { // *=
  real = real * other.real - imaginary * other.imaginary;
  imaginary = real * other.imaginary + imaginary * other.real;
}

void Complex::operator/=(const Complex &other) { // /=
  double denom = other.real * other.real + other.imaginary * other.imaginary;

  real = (real * other.real + imaginary * other.imaginary) / denom;
  imaginary = (imaginary * other.real - real * other.imaginary) / denom;
}

void Complex::operator*=(double scalar) { // *= but with scalar
  real *= scalar;
  imaginary *= scalar;
}

// Comparisons
bool Complex::operator==(const Complex &other) const { // equals
  return real == other.real && imaginary == other.imaginary;
}

bool Complex::operator!=(const Complex &other) const { // not equals
  return !(*this == other);
}

// Math
double Complex::norm() const {
  return real * real + imaginary * imaginary;
} // norm

double Complex::abs() const { return std::sqrt(norm()); } // absolute value

double Complex::arg() const {
  return std::atan2(imaginary, real);
} // phase angle

Complex Complex::conj() const {
  return Complex(real, -imaginary);
} // Complex conjugate

// Getters
double Complex ::get_real() const { return real; } // real component

double Complex::get_imag() const { return imaginary; } // imaginary component
