#include "VM.hpp"

void VM::run(const Program &program) { // run code
  pc = 0;                              // program counter

  while (pc < program.instructions.size()) {            // while not at end
    const Instruction &inst = program.instructions[pc]; // grab next instruction

    switch (inst.op) { // depending on operation

    case OpCode::Init: // initialize number of qubits
      state.initialize(inst.imm);
      break;

    case OpCode::End: // if at end, end code
      return;

    default: // if not implemented yet, just break
      break;
    }

    ++pc;
  }
}
