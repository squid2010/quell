#include "VM.hpp"

#include <iostream>

void VM::run(const Program &program) { // run code
  pc = 0;                              // program counter

  while (pc < program.instructions.size()) {            // while not at end
    const Instruction &inst = program.instructions[pc]; // grab next instruction

    switch (inst.op) { // depending on operation

    case OpCode::Init: // initialize number of qubits
      state.initialize(inst.imm);
      break;

    case OpCode::Gate:
      switch (inst.gate) {
      case GateID::X:
        state.applyX(inst.targetQubit);
        break;

      case GateID::Y:
        state.applyY(inst.targetQubit);
        break;

      case GateID::Z:
        state.applyZ(inst.targetQubit);
        break;

      case GateID::H:
        state.applyH(inst.targetQubit);
        break;

      case GateID::CX:
        state.applyCX(*inst.control, inst.targetQubit);
        break;

      default:
        break;
      }
      break;

    case OpCode::Measure: {
      bool result = state.measure(inst.targetQubit);

      // temporarily print
      std::cout << result << '\n'; // TODO: make this get saved to a creg
    } break;

    case OpCode::End: // if at end, end code
      return;

    default: // if not implemented yet, just break
      break;
    }

    ++pc;
  }
}
