#include "StateVector.hpp"
#include "RNG.hpp"
#include <cmath>
#include <stdexcept>

size_t
Statevector::dimension() const { // return number of dimensions (2^num_qubits)
  return 1ULL << num_qubits;     // Make a 64-bit integer ...001, and then shift
                                 // num_qubits
}

// Constructors
Statevector::Statevector(size_t n_qubits)
    : num_qubits(n_qubits) { // make num_qubits
  size_t dim = dimension();  // set dimension
  for (size_t i = 0; i < dim; ++i)
    data.push_back(Complex()); // add enough spots to array

  data[0] = Complex(1.0, 0.0); // Default to ket 0
}

Statevector::Statevector(const DynamicArray<Complex> &amplitudes,
                         size_t n_qubits)
    : data(amplitudes),
      num_qubits(n_qubits) { // make statevector from amplitude array
  if (data.get_size() != dimension())
    throw std::runtime_error("Statevector size mismatch");
}

// Access
Complex &Statevector::operator[](size_t index) { // [] modify
  return data[index];
}

const Complex &Statevector::operator[](size_t index) const { // [] Access
  return data[index];
}

size_t Statevector::size() const { // size
  return data.get_size();
}

size_t Statevector::qubits() const { // number of qubits
  return num_qubits;
}

// Operations
void Statevector::normalize() { // normalize (divide by magnitutde)
  double norm = 0.0;
  for (size_t i = 0; i < size(); ++i)
    norm += data[i].norm();

  norm = std::sqrt(norm);

  for (size_t i = 0; i < size(); ++i)
    data[i] *= (1 / norm);
}

size_t Statevector::measure(RNG &rng) {
  size_t dim = dimension();
  if (dim == 0) // can't measure nothing
    throw std::runtime_error("Empty statevector");

  // Build probability distribution
  DynamicArray<double> probs;
  probs.resize(dim);
  double sum = 0.0;

  for (size_t i = 0; i < dim; ++i) {
    double p = data[i].norm(); // |amp|^2
    probs.push_back(p);
    sum += p;
  }

  // Normalize probs
  if (sum <= 0.0)
    throw std::runtime_error("Invalid quantum state (zero norm)");

  for (size_t i = 0; i < dim; ++i) {
    probs[i] /= sum;
  }

  // Sample outcome
  size_t outcome = rng.sample(probs);

  // Collapse state
  for (size_t i = 0; i < dim; ++i) {
    if (i != outcome)
      data[i] = Complex(0.0, 0.0); // if not outcome, make everything else 0.0
  }

  // Renormalize state bc keep stable
  double norm = data[outcome].abs();
  if (norm == 0.0)
    throw std::runtime_error("Collapse resulted in zero amplitude");

  for (size_t i = 0; i < dim; ++i) {
    data[i] = data[i] * (1.0 / norm);
  }

  return outcome;
}

Complex
Statevector::inner_product(const Statevector &other) const { // inner product
  if (other.size() != size())
    throw std::runtime_error(
        "Dimension Mismatch"); // must be of same dimension to multiply

  Complex result; // result complex number
  for (size_t i = 0; i < size(); ++i)
    result +=
        data[i].conj() * other[i]; // conjugate transpose of this times other
  return result;
}

void Statevector::apply_gate(
    const Matrix &gate,
    size_t target) { // apply 2x2 gate pairwise (O(2^n))
  if (target >= num_qubits)
    throw std::runtime_error("Invalid qubit index");

  size_t dim = dimension();
  size_t mask = 1ULL << target; // index of target

  for (size_t i = 0; i < dim; i++) {
    if ((i & mask) == 0) { // Process only where target is 0
      size_t j = i | mask; // flip target bit

      Complex a0 = data[i]; // First amplitude
      Complex a1 = data[j]; // Second amplitude

      data[i] = gate(0, 0) * a0 + gate(0, 1) * a1; // Apply to first amplitude
      data[j] = gate(1, 0) * a0 + gate(1, 1) * a1; // Apply to second amplitude
    }
  }
}
