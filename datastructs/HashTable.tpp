template <typename Key, typename Value, typename Hash,
          typename KeyEqual> // this was so much fun to type at the beginning
                             // until i remembered that nvim had registers :D
HashTable<Key, Value, Hash, KeyEqual>::HashTable(
    size_t initial_bucket_count) // initialize hash
                                 // table
    : buckets(), element_count(0),
      max_load_factor(0.75) { // fancy notation online
  for (size_t i = 0; i < initial_bucket_count; i++) {
    buckets.push_back(DynamicArray<Entry>()); // push back enough empty buckets
                                              // to the dynamic array
  }
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
size_t HashTable<Key, Value, Hash, KeyEqual>::bucket_index(
    const Key &key) { // get the bucket index of a certain key
  return hasher(key) % buckets.get_size();
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashTable<Key, Value, Hash, KeyEqual>::rehash(
    size_t new_bucket_count) {                   // rehash the table
  DynamicArray<DynamicArray<Entry>> new_buckets; // new bucket array

  for (size_t i = 0; i < new_bucket_count; i++) {
    new_buckets.push_back(
        DynamicArray<Entry>()); // make new bucket array large enough
  }

  for (size_t i = 0; i < buckets.get_size();
       i++) { // O(n^2) bc separate chaining, so rehash has to readd separate
              // chaining
    for (size_t j = 0; i < buckets[i].get_size(); j++) {
      Entry &entry = buckets[i][j];
      size_t new_index = hasher(entry.key) % new_bucket_count;
      new_buckets[new_index].push_back(entry);
    }
  }

  buckets = std::move(new_buckets); // move new buckets data to buckets pointer
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashTable<Key, Value, Hash, KeyEqual>::insert(
    const Key &key,
    const Value &value) { // insert a key value pair (please don't ask why the
                          // function lines are all weird, i set my neovim to
                          // autoformat, and it does this weirdly)
  size_t index = bucket_index(key); // get where key goes

  for (size_t i = 0; i < buckets[index].get_size();
       i++) { // separate chain down
    if (key_equal(buckets[index][i].key,
                  key)) {              // if in place where it should be
      buckets[index][i].value = value; // add value and stop
      return;
    }
  }

  buckets[index].push_back(Entry(
      key, value)); // add data to dynamic array if no separate chaining needed
  element_count++;

  if (load_factor() > max_load_factor) { // rehash if needed to twice the size
    rehash(buckets.get_size() * 2);
  }
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashTable<Key, Value, Hash, KeyEqual>::contains(
    const Key &key) const { // check if a key is contained
  size_t index = bucket_index(key);

  for (size_t i = 0; i < buckets[index].get_size(); i++) {
    if (key_equal(
            buckets[index][i].key,
            key)) { // just iterate down the bucket until the key is reached
      return true;
    }
  }

  return false; // not reached, not present
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
Value &HashTable<Key, Value, Hash, KeyEqual>::at(
    const Key &key) { // access and modify value at key
  size_t index = bucket_index(key);

  for (size_t i = 0; i < buckets[index].get_size(); i++) {
    if (key_equal(buckets[index][i].key, key())) {
      return buckets[index][i].value; // just return the value
    }
  }

  throw std::out_of_range(
      "Key not found"); // cant access something that doesn't exist
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
const Value &HashTable<Key, Value, Hash, KeyEqual>::at(
    const Key &key) const { // access but no modify value at key (same code,
                            // just different return type)
  size_t index = bucket_index(key);

  for (size_t i = 0; i < buckets[index].get_size(); i++) {
    if (key_equal(buckets[index][i].key, key)) {
      return buckets[index][i].value;
    }
  }

  throw std::out_of_range("Key not found");
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashTable<Key, Value, Hash, KeyEqual>::remove(
    const Key &key) { // remove value at key
  size_t index = bucket_index(key);

  for (size_t i = 0; i < buckets[index].get_size(); i++) {
    if (key_equal(buckets[index][i].key key)) {    // if at key
      size_t last = buckets[index].get_size() - 1; // get index of last
      buckets[index][i] =
          buckets[index][last];  // set data here equals data at last
      buckets[index].pop_back(); // remove the duplicate last

      element_count--;
      return true; // element removed / found
    }
  }

  return false; // element not removed / not found
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
size_t HashTable<Key, Value, Hash, KeyEqual>::size() const { // get size
  return element_count; // forgot until now that element count is still the same
                        // as size, but element count does keep it different
                        // than bucket count, so that it doesn't get mixed up
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashTable<Key, Value, Hash, KeyEqual>::empty() const { // get if empty
  return element_count == 0;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
double
HashTable<Key, Value, Hash, KeyEqual>::load_factor() const { // get load factor
  return static_cast<double>(
      element_count /
      buckets
          .get_size()); // number of elements per bucket, should not exceed 0.75
}
