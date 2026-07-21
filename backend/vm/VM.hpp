#ifndef VM_HPP
#define VM_HPP

#include "../classical/ClassicalRegister.hpp"
#include "../quantum/QuantumRegister.hpp"
#include "../quantum/Statevector.hpp"
#include "Program.hpp"
#include "StackFrame.hpp"
#include <cstddef>
#include <vector>

class VM {
public:
  void run(const Program &program);

private:
  size_t pc = 0;
  Statevector state;                    // vm owns quantum state
  std::vector<ClassicalRegister> cRegs; // list of classical registers
  std::vector<QuantumRegister> qRegs;   // list of quantum registers
  std::vector<StackFrame> callStack;    // for tracking function calls

  size_t resolveQubit(const Address &addr) const; // resolve a qubit's address
};

#endif
