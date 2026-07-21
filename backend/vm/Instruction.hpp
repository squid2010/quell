#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstddef>
#include <optional>

enum class GateID { // default supported set of gates
  I,
  H,
  X,
  Y,
  Z,
  S,
  T,
  SDG,
  TDG, // one qubit gates
  RX,
  RY,
  RZ,
  PHASE, // parameterized gates
  CX,    // two qubit controlled gates (CX and SWAP will get lowered)
};

enum class OpCode { // op codes (duh)
  Gate,
  Measure,
  Reset,
  Init, // basic quantum ops
  MovImm,
  Mov,
  Add,
  Sub,
  Mul,
  Div, // basic classical vm opps
  CmpEq,
  CmpNe,
  CmpLt,
  CmpLe,
  CmpGt,
  CmpGe, // classical comparisons - 0 or 1
  Jmp,
  JmpIfZero,
  JmpIfNonZero, // control flow, relative to pc
  Push,
  Pop,
  ArgLoad,
  Call,
  Ret, // call stack stuff - recursion
  GateR1,
  GateR2,
  InitR,
  MeasureR, // dynamic qubit/bit addressing
  End       // end of code
};

struct Address { // address for a reference to a bit/qubit
  size_t reg;    // register
  size_t index;  // actual index in register
};

struct Instruction {        // machine code instructions
  OpCode op = OpCode::Gate; // op code defaults to a gate
  GateID gate =
      GateID::I; // default gate is identity - does nothing as a fallback
  std::optional<double>
      parameter; // optional parameter - for rotations and phase

  Address qubit; // target qubit
  Address bit;   // target bit - measuring, etc

  std::optional<Address> control; // control qubit index

  size_t dst = 0;  // destionation register
  size_t src1 = 0; // source register (first input value)
  size_t src2 = 0; // source register (second input value)
  long long imm =
      0; // immediate = constant value, not in a register - hard-coded
};

#endif
