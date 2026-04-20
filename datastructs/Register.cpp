#include "Register.hpp"
#include <stdexcept>

Register::Register(size_t n_qubits)
    : num_qubits(n_qubits), initial_state(n_qubits) {} // |00...>
Register::Register(const Statevector &initial)
    : num_qubits(initial.qubits()), initial_state(initial) {
} // start from certain initial Statevector

void Register::add_gate(const Matrix &gate, size_t target) {
  if (target >= num_qubits)
    throw std::runtime_error("Invalid qubit index in Register::add_gate");
  operations.push_back(GateOperation(gate, target));
}

Statevector Register::execute() const {
  Statevector state = initial_state;

  for (size_t i = 0; i < operations.get_size(); ++i) {
    state.apply_gate(operations[i].gate, operations[i].target);
  }

  return state;
}

size_t Register::execute_and_measure(RNG &rng) const {
  Statevector state = execute();
  return state.measure(rng);
}

size_t Register::qubits() const { return num_qubits; }

size_t Register::gate_count() const { return operations.get_size(); }
