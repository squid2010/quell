#ifndef BACKEND_HPP
#define BACKEND_HPP

#include "../datastructs/DynamicArray.hpp"
#include "../datastructs/HashTable.hpp"
#include "../datastructs/Matrix.hpp"
#include "../datastructs/RNG.hpp"
#include "../datastructs/StateVector.hpp"
#include "../datastructs/String.hpp"
#include "Instruction.hpp"
#include <cstddef>

class Backend {
private:
  DynamicArray<Instruction> program;
  HashTable<size_t, size_t> histogram;

  size_t num_qubits;
  size_t num_bits;
  size_t num_shots;

  Statevector last_state;
  bool has_last_state;

  // Parsing stuff
  GateID parse_gate_name(const String &name) const;
  Instruction parse_instruction_line(const String &line) const;
  Matrix resolve_gate(GateID id, const std::optional<double> &param) const;

  // Execution stuff
  void measure_qubit(Statevector &state, size_t qubit, size_t &result,
                     RNG &rng) const;
  void collapse_qubit(Statevector &state, size_t qubit, size_t value) const;
  size_t encode_bits(const DynamicArray<size_t> &bits) const;

public:
  Backned();

  void load(const String &filepath);
  void run(RNG &rng);

  const Statevector &get_statevector() const;
  const HashTable<size_t, size_t> &get_histogram() const;

  size_t shots() const;
  size_t qubits() const;
  size_t bits() const;
};

#endif
