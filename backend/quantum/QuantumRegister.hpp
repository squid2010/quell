#ifndef QUANTUM_REGISTER_HPP
#define QUANTUM_REGISTER_HPP

#include <cstddef>

class QuantumRegister { // this is used to convert from register 3 qubit 2 to
                        // global index of qubit for vm
public:
  size_t id;    // name of register
  size_t start; // start of which qubits it owns
  size_t size;  // how many qubits it owns

  size_t physicalIndex(size_t offset) const; // actual physical index of qubit
};

#endif
