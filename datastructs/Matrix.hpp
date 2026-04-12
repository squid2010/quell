#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Complex.hpp" // matrix made of Complex numbers

class Matrix {
private:
  Complex m[2]
           [2]; // main data structure is 2x2 array, cause all gates can be
                // decomposed into 2x2 matrices along with a CNOT, so this is
                // all i need (CNOT will be implemented into backend directly)
public:
  // Constructors
  Matrix(); // zero matrix
  Matrix(const Complex &a00, const Complex &a01, const Complex &a10,
         const Complex &a11);

  // Static Constructors
  static Matrix identity(); // identity matrix

  // Element access
  Complex &operator()(int row, int col);             // modify
  const Complex &operator()(int row, int col) const; // get

  // Arithmetic
  Matrix operator+(const Matrix &other) const; // addition
  Matrix operator-(const Matrix &other) const; // subtraction
  Matrix operator*(const Matrix &other) const; // multiplication (no division)
  Matrix operator*(Complex scalar) const;      // scalar multiplication

  // Compound Assignment Operators
  void operator+=(const Matrix &other); // +=
  void operator-=(const Matrix &other); // -=
  void operator*=(const Matrix &other); // matrix *=
  void operator*=(Complex scalar);      // scalar *=

  // Matrix operations
  Complex determinant() const; // get determinant (ad - bc)
  Complex trace() const;       // get trace of Matrix
  Matrix inverse() const;      // get inverse matrix
  Matrix transpose() const;    // get transposed matrix
  Matrix conjugate() const;    // get conjugate matrix
  Matrix hermitian() const;    // get hermitian (conjugate transpose)

  // Comparison
  bool operator==(const Matrix &other) const; // is equal
  bool operator!=(const Matrix &other) const; // isn't equal
};

#endif
