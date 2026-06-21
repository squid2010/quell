#include "backend/vm/Instruction.hpp"
#include <gtest/gtest.h>

TEST(InstructionTest, DefaultConstructor) {
  Instruction inst;

  EXPECT_EQ(inst.op, OpCode::Gate);
  EXPECT_EQ(inst.gate, GateID::I);

  EXPECT_FALSE(inst.control.has_value());
  EXPECT_FALSE(inst.parameter.has_value());

  EXPECT_EQ(inst.targetQubit, 0u);
  EXPECT_EQ(inst.targetBit, 0u);

  EXPECT_EQ(inst.dst, 0u);
  EXPECT_EQ(inst.src1, 0u);
  EXPECT_EQ(inst.src2, 0u);

  EXPECT_EQ(inst.imm, 0);
}

TEST(InstructionTest, QuantumGateInstruction) {
  Instruction inst;

  inst.op = OpCode::Gate;
  inst.gate = GateID::H;
  inst.targetQubit = 3;

  EXPECT_EQ(inst.op, OpCode::Gate);
  EXPECT_EQ(inst.gate, GateID::H);
  EXPECT_EQ(inst.targetQubit, 3u);

  EXPECT_FALSE(inst.control.has_value());
  EXPECT_FALSE(inst.parameter.has_value());
}

TEST(InstructionTest, ControlledGateInstruction) {
  Instruction inst;

  inst.op = OpCode::Gate;
  inst.gate = GateID::CX;
  inst.control = 1;
  inst.targetQubit = 4;

  ASSERT_TRUE(inst.control.has_value());

  EXPECT_EQ(inst.gate, GateID::CX);
  EXPECT_EQ(inst.control.value(), 1u);
  EXPECT_EQ(inst.targetQubit, 4u);
}

TEST(InstructionTest, ParameterizedGateInstruction) {
  Instruction inst;

  inst.op = OpCode::Gate;
  inst.gate = GateID::RZ;
  inst.parameter = 3.141592653589793;
  inst.targetQubit = 2;

  ASSERT_TRUE(inst.parameter.has_value());

  EXPECT_EQ(inst.gate, GateID::RZ);
  EXPECT_DOUBLE_EQ(inst.parameter.value(), 3.141592653589793);
  EXPECT_EQ(inst.targetQubit, 2u);
}

TEST(InstructionTest, MeasureInstruction) {
  Instruction inst;

  inst.op = OpCode::Measure;
  inst.targetQubit = 5;
  inst.targetBit = 1;

  EXPECT_EQ(inst.op, OpCode::Measure);
  EXPECT_EQ(inst.targetQubit, 5u);
  EXPECT_EQ(inst.targetBit, 1u);
}

TEST(InstructionTest, ClassicalImmediateInstruction) {
  Instruction inst;

  inst.op = OpCode::MovImm;
  inst.dst = 2;
  inst.imm = 42;

  EXPECT_EQ(inst.op, OpCode::MovImm);
  EXPECT_EQ(inst.dst, 2u);
  EXPECT_EQ(inst.imm, 42);
}

TEST(InstructionTest, ClassicalBinaryInstruction) {
  Instruction inst;

  inst.op = OpCode::Add;
  inst.dst = 0;
  inst.src1 = 1;
  inst.src2 = 2;

  EXPECT_EQ(inst.op, OpCode::Add);
  EXPECT_EQ(inst.dst, 0u);
  EXPECT_EQ(inst.src1, 1u);
  EXPECT_EQ(inst.src2, 2u);
}

TEST(InstructionTest, JumpInstruction) {
  Instruction inst;

  inst.op = OpCode::Jmp;
  inst.imm = -5;

  EXPECT_EQ(inst.op, OpCode::Jmp);
  EXPECT_EQ(inst.imm, -5);
}

TEST(InstructionTest, DynamicQuantumInstruction) {
  Instruction inst;

  inst.op = OpCode::GateR2;
  inst.gate = GateID::CX;
  inst.src1 = 3; // control register
  inst.src2 = 4; // targetQubitregister

  EXPECT_EQ(inst.op, OpCode::GateR2);
  EXPECT_EQ(inst.gate, GateID::CX);
  EXPECT_EQ(inst.src1, 3u);
  EXPECT_EQ(inst.src2, 4u);
}
