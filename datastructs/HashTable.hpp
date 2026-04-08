// TODO: comment

#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "DynamicArray.hpp"
#include <functional>
#include <stdexcept>

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>

class HashTable {
private:
  struct Entry {
    Key key;
    Value value;

    Entry(const Key &k, const Value &v) : key(k), value(v) {}
  };

  DynamicArray<DynamicArray<Entry>> buckets;
  size_t element_count;
  double max_load_factor;

  Hash hasher;
  KeyEqual key_equal;

  size_t bucket_index(const Key &key) const;
  void rehash(size_t new_bucket_count);

public:
  HashTable(size_t initial_bucket_count = 16);

  void insert(const Key &key, const Value &value);
  bool contains(const Key &key) const;
  Value &at(const Key &key);
  const Value &at(const Key &key) const;

  bool remove(const Key &key);

  size_t size() const;
  bool empty() const;

  double load_factor() const;
}

#include "HashTable.tpp"

#endif
