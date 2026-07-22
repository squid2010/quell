#include <iostream>

// Mock the required structures for checking
struct Address {
    size_t reg = 0;
    size_t index = 0;
};

enum class OpCode { Gate, Init, Measure, MovImm, Add, Jmp, GateR2 };
enum class GateID { I, H, X, Y, Z, S, T, SDG, TDG, RX, RY, RZ, PHASE };

struct Instruction {
    OpCode op = OpCode::Gate;
    GateID gate = GateID::I;
    std::optional<double> parameter;

    Address qubit;
    Address bit;

    std::optional<Address> control;

    size_t dst = 0;
    size_t src1 = 0;
    size_t src2 = 0;
    long long imm = 0;

    // For backward compatibility with tests
    size_t targetQubit = 0;
    size_t targetBit = 0;
};

int main() {
    Instruction inst;
    inst.qubit.index = 5;
    inst.bit.index = 2;

    // Check that we can access fields
    std::cout << "targetQubit: " << inst.targetQubit << std::endl;
    std::cout << "targetBit: " << inst.targetBit << std::endl;

    return 0;
}