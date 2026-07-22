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

      case GateID::S:
        state.applyS(resolveQubit(inst.qubit));
        break;

      case GateID::T:
        state.applyT(resolveQubit(inst.qubit));
        break;

      case GateID::SDG:
        state.applySDG(resolveQubit(inst.qubit));
        break;

      case GateID::TDG:
        state.applyTDG(resolveQubit(inst.qubit));
        break;

      case GateID::RX:
        if (inst.parameter.has_value()) {
          state.applyRX(resolveQubit(inst.qubit), inst.parameter.value());
        }
        break;

      case GateID::RY:
        if (inst.parameter.has_value()) {
          state.applyRY(resolveQubit(inst.qubit), inst.parameter.value());
        }
        break;

      case GateID::RZ:
        if (inst.parameter.has_value()) {
          state.applyRZ(resolveQubit(inst.qubit), inst.parameter.value());
        }
        break;

      case GateID::PHASE:
        if (inst.parameter.has_value()) {
          state.applyPhase(resolveQubit(inst.qubit), inst.parameter.value());
        }
        break;

      case GateID::CX:
        state.applyCX(resolveQubit(*inst.control), resolveQubit(inst.qubit));
        break;

      default:
        break;
      }
      break;

    case OpCode::GateR1: {
      size_t qubit_index = cRegs[inst.src1].get(inst.dst);
      Instruction new_inst = inst; // Create a copy of the instruction
      new_inst.qubit.reg = 0; // assuming we use the first register for dynamic addressing
      new_inst.qubit.index = qubit_index;
      switch (new_inst.gate) {
        case GateID::S:
          state.applyS(resolveQubit(new_inst.qubit));
          break;
        case GateID::T:
          state.applyT(resolveQubit(new_inst.qubit));
          break;
        case GateID::SDG:
          state.applySDG(resolveQubit(new_inst.qubit));
          break;
        case GateID::TDG:
          state.applyTDG(resolveQubit(new_inst.qubit));
          break;
        case GateID::RX:
          if (new_inst.parameter.has_value()) {
            state.applyRX(resolveQubit(new_inst.qubit), new_inst.parameter.value());
          }
          break;
        case GateID::RY:
          if (new_inst.parameter.has_value()) {
            state.applyRY(resolveQubit(new_inst.qubit), new_inst.parameter.value());
          }
          break;
        case GateID::RZ:
          if (new_inst.parameter.has_value()) {
            state.applyRZ(resolveQubit(new_inst.qubit), new_inst.parameter.value());
          }
          break;
        case GateID::PHASE:
          if (new_inst.parameter.has_value()) {
            state.applyPhase(resolveQubit(new_inst.qubit), new_inst.parameter.value());
          }
          break;
        default:
          // Handle unsupported gates for dynamic addressing
          break;
      }
    } break;

    case OpCode::GateR2: {
      size_t control_index = cRegs[inst.src1].get(inst.dst);
      size_t target_index = cRegs[inst.src2].get(inst.dst);
      Instruction new_inst = inst; // Create a copy of the instruction
      new_inst.qubit.reg = 0; // assuming we use the first register for dynamic addressing
      new_inst.qubit.index = target_index;
      // For GateR2, we need to create a new control qubit
      Address control_qubit;
      control_qubit.reg = 0;
      control_qubit.index = control_index;
      new_inst.control = control_qubit;
      switch (new_inst.gate) {
        case GateID::CX:
          state.applyCX(resolveQubit(*new_inst.control), resolveQubit(new_inst.qubit));
          break;
        default:
          // Handle unsupported gates for dynamic addressing
          break;
      }
    } break;

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
