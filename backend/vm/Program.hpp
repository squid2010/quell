#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Instruction.hpp"
#include <vector>

class Program {
public:
  std::vector<Instruction> instructions;
};

#endif
