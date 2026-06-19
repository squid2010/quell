#ifndef CLASSICAL_REGISTER_HPP
#define CLASSICAL_REGISTER_HPP

#include <cstddef>
#include <vector>

class ClassicalRegister {
private:
  std::vector<long long> values; // values of the register

public:
  long long get(size_t index) const;       // get a value of an index
  void set(size_t index, long long value); // set the value of an index
};
#endif
