// Constructors
template <typename T> DynamicArray<T>::DynamicArray() { // default constructor
  size = 0;
  capacity = 1;
  data = new T[capacity];
}

template <typename T> DynamicArray<T>::~DynamicArray() { // destructor
  delete[] data;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &other) { // copy constructor
  size = other.size;
  capacity = other.capacity;

  data = new T[capacity];

  for (size_t i = 0; i < size; i++) {
    data[i] = other.data[i];
  }
}

template <typename T>
DynamicArray<T>::DynamicArray(
    DynamicArray &&other) noexcept { // move constructor
  data = other.data;
  size = other.size;
  capacity = other.capacity;

  other.data = nullptr;
  other.size = 0;
  other.capacity = 0;
}

// Assigners
template <typename T>
DynamicArray<T> &
DynamicArray<T>::operator=(const DynamicArray &other) { // Copy assignment
  if (this == &other) {
    return *this;
  }

  delete[] data;

  size = other.size;
  capacity = other.capacity;

  data = new T[capacity];

  for (size_t i = 0; i < size; i++) {
    data[i] = other.data[i];
  }

  return *this;
}

template <typename T>
DynamicArray<T> &
DynamicArray<T>::operator=(DynamicArray &&other) noexcept { // Move assignment
  if (this == &other) {
    return *this;
  }

  delete[] data;

  data = other.data;
  size = other.size;
  capacity = other.capacity;

  other.data = nullptr;
  other.size = 0;
  other.capacity = 0;

  return *this;
}

// Access and Modifiers
template <typename T>
void DynamicArray<T>::resize(size_t new_capacity) { // resize if meet capacity
  T *new_data = new T[new_capacity];

  for (size_t i = 0; i < size; i++) {
    new_data[i] = data[i];
  }

  delete[] data;
  data = new_data;
  capacity = new_capacity;
}

template <typename T>
void DynamicArray<T>::push_back(
    const T &value) { // push an element to the array
  if (size == capacity) {
    resize(capacity * 2); // double capacity if meet
  }

  data[size++] = value; // add last element to size pos, increase size by one
}

template <typename T>
void DynamicArray<T>::pop_back() { // remove the last element (make it not
                                   // accessable)
  if (size > 0) {
    size--;
  }
}

template <typename T>
T &DynamicArray<T>::operator[](size_t index) { // edit value with []
  return data[index];
}

template <typename T>
const T &DynamicArray<T>::operator[](
    size_t index) const { // get value with [], don't change it
  return data[index];
}

template <typename T> size_t DynamicArray<T>::get_size() const { // get size;
  return size;
}
