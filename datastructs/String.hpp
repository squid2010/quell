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

  // Equality operator
  bool operator==(const String &other) const;
  bool operator!=(const String &other) const;

  // Methods
  size_t size() const;
  const char *c_str() const;

  char &operator[](size_t index);
  const char &operator[](size_t index) const;
};

// Make hash stuff for String
#include <functional>

namespace std {
template <> struct hash<String> {
  size_t operator()(const String &s) const {
    const char *str = s.c_str();
    size_t hash = 5381; // djb2
    while (*str) {      // while still values in array
      hash = ((hash << 5) + hash) +
             static_cast<size_t>(*str); // multiply by 33, then add the
                                        // character (magically works ig)
      ++str;                            // move to the next memory address
    }
    return hash;
  }
};
} // namespace std

#endif
