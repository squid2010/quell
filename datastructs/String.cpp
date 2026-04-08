#include "String.hpp"
#include <cstring>

String::String() { // empty constructor
  length = 0;
  data = new char[1];
  data[0] = '\0'; // needs null terminator to be a valid c string
}

String::String(const char *str) { // copy from a c string
  length = std::strlen(str);      // copy length
  data = new char[length + 1];    // enough space for data + null terminator
  std::strcpy(data, str);
}

String::~String() { delete[] data; } // free the memory

String::String(const String &other) { // copy from another reference
  length = other.length;
  data = new char[length + 1];   // data + null terminator
  std::strcpy(data, other.data); // deep copy
}

String &String::operator=(const String &other) {
  if (this == &other) // prevent self assignment
    return *this;

  delete[] data; // free existing memory before replacing

  // same logic as copy constructor
  length = other.length;
  data = new char[length + 1];
  std::strcpy(data, other.data);

  return *this;
}

bool String::operator==(const String &other) const { // equality operator
  if (length != other.length)
    return false;
  return std::strcmp(data, other.data) == 0;
}

bool String::operator!=(const String &other) const { // not equals
  return !(*this == other);
}

// getters
size_t String::size() const { return length; }

const char *String::c_str() const { return data; } // returns internal buffer

char &String::operator[](size_t index) {
  return data[index];
} // access character

const char &String::operator[](size_t index) const {
  return data[index];
} // read-only
