#include "Matrix.hpp"

// Constructors
Matrix::Matrix() { // Make 0 matrix (i considered using a for loop, but this is
                   // easier
  m[0][0] = Complex();
  m[0][1] = Complex();
  m[1][0] = Complex();
  m[1][1] = Complex();
}

Matrix::Matrix(const Complex &a00, const Complex &a01, const Complex &a10,
               const Complex &a11) { // Constructor from vals
  m[0][0] = a00;
  m[0][1] = a01;
  m[1][0] = a10;
  m[1][1] = a11;
}

Matrix Matrix::identity() { // identity matrix
  return Matrix(Complex(1, 0), Complex(0, 0), Complex(0, 0), Complex(1, 0));
}

// Element access
Complex &Matrix::operator()(int row, int col) { // modify
  return m[row][col];
}

const Complex &Matrix::operator()(int row, int col) const { // access
  return m[row][col];
}

// Arithmetic
Matrix Matrix::operator+(const Matrix &other) const { // addition
  return Matrix(m[0][0] + other.m[0][0], m[0][1] + other.m[0][1],
                m[1][0] + other.m[1][0], m[1][1] + other.m[1][1]);
}

Matrix Matrix::operator-(const Matrix &other) const { // subtraction
  return Matrix(m[0][0] - other.m[0][0], m[0][1] - other.m[0][1],
                m[1][0] - other.m[1][0], m[1][1] - other.m[1][1]);
}

Matrix
Matrix::operator*(const Matrix &other) const { // multiplication (more work)
  return Matrix(m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0],
                m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1],
                m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0],
                m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1]);
}

Matrix Matrix::operator*(Complex scalar) const { // scalar multiplication
  return Matrix(m[0][0] * scalar, m[0][1] * scalar, m[1][0] * scalar,
                m[1][1] * scalar);
}

// Compound assignment
void Matrix::operator+=(const Matrix &other) { //  +=
  m[0][0] += other.m[0][0];
  m[0][1] += other.m[0][1];
  m[1][0] += other.m[1][0];
  m[1][1] += other.m[1][1];
}

void Matrix::operator-=(const Matrix &other) { // -=
  m[0][0] -= other.m[0][0];
  m[0][1] -= other.m[0][1];
  m[1][0] -= other.m[1][0];
  m[1][1] -= other.m[1][1];
}

void Matrix::operator*=(const Matrix &other) { // *=, found an easier way online
  *this = (*this) * other; // set this object to point to result of multiplying
                           // this with other
}

void Matrix::operator*=(Complex scalar) { // scalar *=
  m[0][0] *= scalar;
  m[0][1] *= scalar;
  m[1][0] *= scalar;
  m[1][1] *= scalar;
}

// Matrix Operations
Complex Matrix::determinant() const { // ad - bc
  return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

Complex Matrix::trace() const { // sum of elements along diagonal
  return m[0][0] + m[1][1];
}

Matrix Matrix::inverse() const { // A*A⁻¹ = I
  Complex coeff =
      Complex(1, 0) / determinant(); // no scalar division, just do this
  Matrix inverse =
      Matrix(m[1][1], m[0][1] * -1, m[1][0] * -1, m[0][0]); // d, -b, -c, a
  return inverse * coeff;
}

Matrix Matrix::transpose() const { // tranpose the matrix
  return Matrix(m[0][0], m[1][0], m[0][1], m[1][1]);
}

Matrix Matrix::conjugate() const { // conjugate each elements
  return Matrix(m[0][0].conj(), m[0][1].conj(), m[1][0].conj(), m[1][1].conj());
}

Matrix Matrix::hermitian() const { // conjugate transpose
  return conjugate().transpose();
}

// Comparison
bool Matrix::operator==(const Matrix &other) const { // equality
  return m[0][0] == other.m[0][0] && m[0][1] == other.m[0][1] &&
         m[1][0] == other.m[1][0] && m[1][1] == other.m[1][1];
}

bool Matrix::operator!=(const Matrix &other) const { // not equal
  return !(*this == other);
}
