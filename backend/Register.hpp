#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "DynamicArray.hpp"
#include "Matrix.hpp"
#include "RNG.hpp"
#include "StateVector.hpp"
#include <cstddef>
#include <optional>

class Register {
private:
  struct GateOperation {           // substitute for later instruction
    Matrix gate;                   // matrix
    size_t target;                 // target value
    std::optional<size_t> control; // no control = std::nullopt

    GateOperation(const Matrix &g, size_t t, size_t c) // controlled matrix
        : gate(g), target(t), control(c) {}
    GateOperation(const Matrix &g, size_t t) // uncontrolled matrix
        : gate(g), target(t), control(std::nullopt) {}
    GateOperation()
        : gate(Matrix::identity()), target(0), control(std::nullopt) {
    } // used by DynamicArray to create empty gateoperations
  };

  size_t num_qubits;                      // num_qubits
  Statevector initial_state;              // initial statevector
  DynamicArray<GateOperation> operations; // dynamic array of instrutions

public:
  // Constructors
  explicit Register(
      size_t n_qubits); // explicit constructor from number of qubits
  Register(const Statevector &initial); // constructor from initial state

  void add_gate(const Matrix &gate, size_t target); // add gate
  void add_gate(const Matrix &gate, size_t target,
                size_t control); // add controlled gate
  Statevector execute() const;   // run the Register
  size_t
  execute_and_measure(RNG &rng) const; // run the circuit, then measure it

  size_t qubits() const;     // num_qubits
  size_t gate_count() const; // circuit depth
};

#endif
