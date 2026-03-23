#ifndef COMPLEX_HPP
#define COMPLEX_HPP

class Complex {
private:
  double real;
  double imaginary;

public:
  // Constructor
  Complex();                                          // Default Cnstructor
  Complex(const double real, const double imaginary); // Constructor from value

  // Arithmetic
  Complex operator+(const Complex &other) const; // addition
  Complex operator-(const Complex &other) const; // subtraction
  Complex operator*(const Complex &other) const; // multiplication
  Complex operator/(const Complex &other) const; // division

  Complex operator*(const double scalar) const; // Scalar multiplication

  // Compound operators
  void operator+=(const Complex &other); // += operator
  void operator-=(const Complex &other); // -= operator
  void operator*=(const Complex &other); // *= operator
  void operator/=(const Complex &other); // /= operator

  void operator*=(const double scalar); // *= scalar operator

  // Comparisons
  bool operator==(const Complex &other) const; // equality
  bool operator!=(const Complex &other) const; // not equal

  // Math
  double abs() const;  // magnitude
  double norm() const; // norm (squared magnitude)
  double arg() const;  // phase angle

  Complex conj() const; // complex conjugate

  // Getters
  double get_real() const; // real
  double get_imag() const; // imaginary
};

#endif
