#include <stdexcept>

template <typename T> Stack<T>::Stack() {} // Constructor

template <typename T> void Stack<T>::push(const T &value) { // Push
  data.push_back(value);
}

template <typename T> void Stack<T>::pop() { // Pop
  if (empty()) {
    throw std::out_of_range("Stack is empty");
  }
  data.pop_back();
}

template <typename T> T &Stack<T>::peek() { // Peek
  if (empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return data[data.get_size() - 1];
}

template <typename T>
const T &Stack<T>::peek() const { // Peek but don't change anything
  if (empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return data[data.get_size() - 1];
}

template <typename T> bool Stack<T>::empty() const {
  return data.get_size() == 0;
} // is empty

template <typename T> size_t Stack<T>::size() const {
  return data.get_size();
} // size
