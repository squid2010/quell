#include "ClassicalRegister.hpp"

long long ClassicalRegister::get(size_t index) const { // get value at an index
  return values.at(index);
}

void ClassicalRegister::set(size_t index,
                            long long value) { // set value at an index
  if (index >= values.size())                  // resize if not enough space
    values.resize(index + 1);

  values[index] = value;
}
