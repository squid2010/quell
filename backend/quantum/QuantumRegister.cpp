#include "QuantumRegister.hpp"

size_t QuantumRegister::physicalIndex(size_t offset) const {
  return start + offset; // physical index of qubit
}
