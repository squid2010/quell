#ifndef STRING_HPP
#define STRING_HPP
#include <cstddef> // for size_t

class String {
private:
  char *data;
  size_t length;

public:
  // constructors
  String();
  String(const char *str);

  // Destructor
  ~String();

  // Copy constructor
  String(const String &other);

  // Assignment operator
  String &operator=(const String &other);

  // Methods
  size_t size() const;
  const char *c_str() const;

  char &operator[](size_t index);
  const char &operator[](size_t index) const;
};

#endif
