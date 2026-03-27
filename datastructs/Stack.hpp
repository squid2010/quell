#ifndef STACK_HPP
#define STACK_HPP

#include "DynamicArray.hpp"

template <typename T> class Stack {
private:
  DynamicArray<T> data; // internal data as Dynamic Array

public:
  Stack(); // default constructor

  void push(const T &value); // push to top
  void pop();                // get rid of top

  T &peek(); // peek at top value (called on mutable stacks, modifable
             // reference)
  const T &peek() const; // peek at top value (called on consts, read-only)

  bool empty() const;  // is empty or not
  size_t size() const; // get size
};

#include "Stack.tpp"

#endif
