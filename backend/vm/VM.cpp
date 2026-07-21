#include "VM.hpp"

size_t
VM::resolveQubit(const Address &addr) const { // return global index of qubit
  return qRegs.at(addr.reg).physicalIndex(addr.index);
}

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
        state.applyX(resolveQubit(inst.qubit));
        break;

      case GateID::Y:
        state.applyY(resolveQubit(inst.qubit));
        break;

      case GateID::Z:
        state.applyZ(resolveQubit(inst.qubit));
        break;

      case GateID::H:
        state.applyH(resolveQubit(inst.qubit));
        break;

      case GateID::CX:
        state.applyCX(resolveQubit(*inst.control), resolveQubit(inst.qubit));
        break;

      default:
        break;
      }
      break;

    case OpCode::Measure: {
      bool result = state.measure(resolveQubit(inst.qubit));

      cRegs[inst.bit.reg].set(inst.bit.index, result); // save result to creg
    } break;

    case OpCode::End: // if at end, end code
      return;

    default: // if not implemented yet, just break
      break;
    }

    ++pc;
  }
}
