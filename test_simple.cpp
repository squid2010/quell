#include "backend/vm/Program.hpp"
#include "backend/vm/VM.hpp"

#include <iostream>

int main() {
    Program program;

    // INIT 2
    {
        Instruction inst;
        inst.op = OpCode::Init;
        inst.imm = 2;
        program.instructions.push_back(inst);
    }

    // H q0
    {
        Instruction inst;
        inst.op = OpCode::Gate;
        inst.gate = GateID::H;
        inst.qubit.reg = 0;
        inst.qubit.index = 0;
        program.instructions.push_back(inst);
    }

    // CX q0 q1
    {
        Instruction inst;
        inst.op = OpCode::Gate;
        inst.gate = GateID::CX;
        inst.control = std::optional<Address>(Address{0, 0});
        inst.qubit.reg = 0;
        inst.qubit.index = 1;
        program.instructions.push_back(inst);
    }

    // Measure q0
    {
        Instruction inst;
        inst.op = OpCode::Measure;
        inst.qubit.reg = 0;
        inst.qubit.index = 0;
        program.instructions.push_back(inst);
    }

    // Measure q1
    {
        Instruction inst;
        inst.op = OpCode::Measure;
        inst.qubit.reg = 0;
        inst.qubit.index = 1;
        program.instructions.push_back(inst);
    }

    // End
    {
        Instruction inst;
        inst.op = OpCode::End;
        program.instructions.push_back(inst);
    }

    VM vm;
    std::cout << "About to run VM..." << std::endl;
    vm.run(program);
    std::cout << "VM finished." << std::endl;

    return 0;
}