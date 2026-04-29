#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstddef>
#include <optional>

enum class GateID { // individual gates
  I,
  H,
  X,
  Y,
  Z,
  S,
  T,
  S_DAG,
  T_DAG, // basic one qubit gates
  RX,
  RY,
  RZ,
  PHASE, // parameterized gates
  CNOT,
  CZ // two qubit controlled gates
};

enum class OpCode { // operation codes
  Gate,
  Measure,
  Init,
  End
};

struct Instruction {               // individual instructions
  OpCode op = OpCode::Gate;        // default opcode is a gate
  GateID gate = GateID::I;         // default instruction is an Identity
  std::optional<size_t> control;   // optional control qubit
  std::optional<double> parameter; // optional parameterized gate
  size_t target = 0;               // target qubit
  size_t bit = 0;                  // target bit (for measurement)
};

#endif
