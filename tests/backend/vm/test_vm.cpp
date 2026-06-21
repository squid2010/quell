#include "backend/vm/Program.hpp"
#include "backend/vm/VM.hpp"

#include <gtest/gtest.h>

TEST(BellState, CorrelatedMeasurements) {
  constexpr int NUM_SHOTS = 1000;

  int count00 = 0;
  int count11 = 0;
  int count01 = 0;
  int count10 = 0;

  for (int shot = 0; shot < NUM_SHOTS; ++shot) {
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
      inst.targetQubit = 0;
      program.instructions.push_back(inst);
    }

    // CX q0 q1
    {
      Instruction inst;
      inst.op = OpCode::Gate;
      inst.gate = GateID::CX;
      inst.control = 0;
      inst.targetQubit = 1;
      program.instructions.push_back(inst);
    }

    // Measure q0
    {
      Instruction inst;
      inst.op = OpCode::Measure;
      inst.targetQubit = 0;
      program.instructions.push_back(inst);
    }

    // Measure q1
    {
      Instruction inst;
      inst.op = OpCode::Measure;
      inst.targetQubit = 1;
      program.instructions.push_back(inst);
    }

    // End
    {
      Instruction inst;
      inst.op = OpCode::End;
      program.instructions.push_back(inst);
    }

    testing::internal::CaptureStdout();

    VM vm;
    vm.run(program);

    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_GE(output.size(), 4u);

    int q0 = output[0] - '0';
    int q1 = output[2] - '0';

    if (q0 == 0 && q1 == 0)
      ++count00;
    else if (q0 == 1 && q1 == 1)
      ++count11;
    else if (q0 == 0 && q1 == 1)
      ++count01;
    else if (q0 == 1 && q1 == 0)
      ++count10;
  }

  EXPECT_EQ(count01, 0);
  EXPECT_EQ(count10, 0);

  EXPECT_GT(count00, NUM_SHOTS / 4);
  EXPECT_GT(count11, NUM_SHOTS / 4);
}
