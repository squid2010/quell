#ifndef VM_HPP
#define VM_HPP

#include "Program.hpp"
#include <cstddef>

class VM {
public:
  void run(const Program &program);

private:
  size_t pc = 0;
};

#endif
