#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef> // has size_t

template <typename T> // template (not inheritance, cause a stack isn't a
                      // dynamic array)

class DynamicArray {
private:
  T *data;
  size_t size;
  size_t capacity;

  void grow();

public:
  // Rule of 5
  DynamicArray();                                         // constructor
  ~DynamicArray();                                        // destructor
  DynamicArray(const DynamicArray &other);                // copy constuctor
  DynamicArray &operator=(const DynamicArray &other);     // copy assignment
  DynamicArray(DynamicArray &&other) noexcept;            // move constructor
  DynamicArray &operator=(DynamicArray &&other) noexcept; // move assignment

  // Access & Modifiers
  void resize(size_t new_capacity);        // resize the capacity of the array
  void push_back(const T &value);          // push a value to the dynamic array
  void pop_back();                         // pop a value out
  T &operator[](size_t index);             // [] for changing
  const T &operator[](size_t index) const; // [] for accessing
  size_t get_size() const;                 // size
};

#include "DynamicArray.tpp" // implementations in the template file

#endif
