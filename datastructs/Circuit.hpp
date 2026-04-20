#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include "DynamicArray.hpp"
#include "Matrix.hpp"
#include "RNG.hpp"
#include "StateVector.hpp"
#include <cstddef>

class Circuit {
private:
  struct GateOperation { // substitute for later instruction
    Matrix gate;
    size_t target;

    GateOperation(const Matrix &g, size_t t) : gate(g), target(t) {}
  };

  size_t num_qubits;
  Statevector initial_state;
  DynamicArray<GateOperation> operations;

public:
  // Constructors
  explicit Circuit(size_t n_qubits);
  Circuit(const Statevector &initial);

  void add_gate(const Matrix &gate, size_t target); // add gate
  Statevector execute() const;                      // run the Circuit
  size_t
  execute_and_measure(RNG &rng) const; // run the circuit, then measure it

  size_t qubits() const;     // num_qubits
  size_t gate_count() const; // circuit depth
};

#endif
