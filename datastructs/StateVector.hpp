#ifndef STATEVECTOR_HPP
#define STATEVECTOR_HPP

#include "Complex.hpp"
#include "DynamicArray.hpp"
#include "Matrix.hpp"
#include "RNG.hpp"
#include <optional>

class Statevector {
private:
  DynamicArray<Complex> data;
  size_t num_qubits;

  size_t dimension() const;

public:
  // Constructors
  Statevector(size_t n_qubits);
  Statevector(const DynamicArray<Complex> &amplitudes, size_t n_qubits);

  // Access
  Complex &operator[](size_t index);
  const Complex &operator[](size_t index) const;

  size_t size() const;
  size_t qubits() const;

  // Operations
  void normalize();
  size_t measure(RNG &rng); // returns measurement as integer
  Complex inner_product(const Statevector &other) const;
  void apply_gate(const Matrix &gate, size_t target,
                  std::optional<size_t> control = std::nullopt);
};

#endif
