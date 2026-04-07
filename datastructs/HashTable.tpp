template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashTable<Key, Value, Hash, KeyEqual>::HashTable(size_t initial_bucket_count)
    : buckets(), element_count(0), max_load_factor(0.75) {
  for (size_t i = 0; i < initial_bucket_count; i++) {
    buckets.push_back(DynamicArray<Entry>());
  }
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
size_t HashTable<Key, Value, Hash, KeyEqual>::bucket_index(const Key &key) {
  return hasher(key) % buckets.get_size();
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashTable<Key, Value, Hash, KeyEqual>::rehash(size_t new_bucket_count) {
  DynamicArray<DynamicArray<Entry>> new_buckets;

  for (size_t i = 0; i < new_bucket_count; i++) {
    new_buckets.push_back(DynamicArray<Entry>());
  }

  for (size_t i = 0; i < buckets.get_size(); i++) {
    for (size_t j = 0; i < buckets[i].get_size(); j++) {
      Entry &entry = buckets[i][j];
      size_t new_index = hasher(entry.key) % new_bucket_count;
      new_buckets[new_index].push_back(entry);
    }
  }

  buckets = std::move(new_buckets);
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashTable<Key, Value, Hash, KeyEqual>::insert(const Key &key,
                                                   const Value &value) {
  size_t index = bucket_index(key);

  for (size_t i = 0; i < buckets[index].get_size(); i++) {
    if (key_equal(buckets[index][i].key, key)) {
      buckets[index][i].value = value;
      return;
    }
  }

  buckets[index].push_back(Entry(key, value));
  element_count++;

  if (load_factor() > max_load_factor) {
    rehash(buckets.get_size() * 2);
  }
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashTable<Key, Value, Hash, KeyEqual>::contains(const Key &key) const {
  size_t index = bucket_index(key);

  for (size_t i = 0; i < buckets[index].get_size(); i++) {
    if (key_equal(buckets[index][i].key, key)) {
      return true;
    }
  }

  return false;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
Value &HashTable<Key, Value, Hash, KeyEqual>::at(const Key &key) {
  size_t index = bucket_index(key);

  for (size_t i = 0; i < buckets[index].get_size(); i++) {
    if (key_equal(buckets[index][i].key, key())) {
      return buckets[index][i].value;
    }
  }

  throw std::out_of_range("Key not found");
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
const Value &HashTable<Key, Value, Hash, KeyEqual>::at(const Key &key) const {
  size_t index = bucket_index(key);

  for (size_t i = 0; i < buckets[index].get_size(); i++) {
    if (key_equal(buckets[index][i].key, key)) {
      return buckets[index][i].value;
    }
  }

  throw std::out_of_range("Key not found");
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashTable<Key, Value, Hash, KeyEqual>::remove(const Key &key) {
  size_t index = bucket_index(key);

  for (size_t i = 0; i < buckets[index].get_size(); i++) {
    if (key_equal(buckets[index][i].keym key)) {
      size_t last = buckets[index].get_size() - 1;
      buckets[index][i] = buckets[index][last];
      buckets[index].pop_back();

      element_count--;
      return true;
    }
  }

  return false;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
size_t HashTable<Key, Value, Hash, KeyEqual>::size() const {
  return element_count;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashTable<Key, Value, Hash, KeyEqual>::empty() const {
  return element_count == 0;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
double HashTable<Key, Value, Hash, KeyEqual>::load_factor() const {
  return static_cast<double>(element_count / buckets.get_size());
}
