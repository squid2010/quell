#include "Circuit.hpp"
#include <stdexcept>

Circuit::Circuit(size_t n_qubits)
    : num_qubits(n_qubits), initial_state(n_qubits) {} // |00...>
Circuit::Circuit(const Statevector &initial)
    : num_qubits(initial.qubits()), initial_state(initial) {
} // start from certain initial Statevector

void Circuit::add_gate(const Matrix &gate, size_t target) {
  if (target >= num_qubits)
    throw std::runtime_error("Invalid qubit index in Circuit::add_gate");
  operations.push_back(GateOperation(gate, target));
}

Statevector Circuit::execute() const {
  Statevector state = initial_state;

  for (size_t i = 0; i < operations.get_size(); ++i) {
    state.apply_gate(operations[i].gate, operations[i].target);
  }

  return state;
}

size_t Circuit::execute_and_measure(RNG &rng) const {
  Statevector state = execute();
  return state.measure(rng);
}

size_t Circuit::qubits() const { return num_qubits; }

size_t Circuit::gate_count() const { return operations.get_size(); }
