#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "DynamicArray.hpp"
#include <functional> // need for hash
#include <stdexcept>  // used by tpp

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename KeyEqual =
              std::equal_to<Key>> // use any key, value, and hash combo

class HashTable {
private:
  struct Entry {
    Key key;
    Value value;

    Entry(const Key &k, const Value &v)
        : key(k), value(v) {} // fancy notation i found
  };

  DynamicArray<DynamicArray<Entry>> buckets; // uses separate chaining
  size_t
      element_count; // size (different name bc i forgot how separate chaining
                     // worked, and now it is too much work to change it
  double max_load_factor; // load_factor to tell when to resize

  Hash hasher;        // hash function
  KeyEqual key_equal; // equal function for key

  size_t bucket_index(const Key &key) const; // returns index of a bucket
  void rehash(size_t new_bucket_count);      // rehashes the array

public:
  HashTable(size_t initial_bucket_count = 16); // default inital size is 16

  void insert(const Key &key, const Value &value); // insert a key value pair
  bool contains(const Key &key) const;             // check if a key is present
  Value &at(const Key &key); // modify value at certain key (reference)
  const Value &at(const Key &key) const; // access value at key (reference)

  bool remove(const Key &key); // remove key value pair

  size_t size() const; // return size
  bool empty() const;  // get is empty

  double load_factor() const; // return current load factor
}

#include "HashTable.tpp" // implementation

#endif
