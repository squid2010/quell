template <typename T> DynamicArray<T>::DynamicArray() { // empty constructor
  size = 0;
  capacity = 1;
  data = new T[capacity];
}

template <typename T> DynamicArray<T>::~DynamicArray() {
  delete[] data;
} // destructor

template <typename T>
void DynamicArray<T>::push_back(const T &value) { // push_back function
  if (size == capacity) {                         // resize if needed
    capacity *= 2;                                // double size

    T *new_data = new T[capacity];
    for (size_t i = 0; i < size; i++) {
      new_data[i] = data[i];
    }

    delete[] data; // delete old data before setting it
    data = new_data;
  }

  data[size++] =
      value; // increment size by 1 and set the new spot to the inputed value
}
