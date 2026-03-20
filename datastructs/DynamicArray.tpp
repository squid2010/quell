template <typename T> DynamicArray<T>::DynamicArray() {
  size = 0;
  capacity = 1;
  data = new T[capacity];
}

template <typename T> DynamicArray<T>::~DynamicArray() { delete[] data; }

template <typename T> void DynamicArray<T>::push_back(const T &value) {
  if (size == capacity) {
    capacity *= 2;

    T *new_data = new T[capacity];
    for (size_t i = 0; i < size; i++) {
      new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
  }

  data[size++] = value;
}
