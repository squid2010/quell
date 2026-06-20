#include "Statevector.hpp"

#include <cmath>
#include <utility>

void Statevector::initialize(size_t numQubits) {
  amplitudes.assign(1ULL << numQubits,
                    0); // resize to 2 amplitudes for each qubit, set all to 0
}

void Statevector::applyX(size_t targetQubit) {
  size_t stride = 1ULL << targetQubit; // spacing between pairs of states where
                                       // target qubit changes from 0 to 1

  for (size_t i = 0; i < amplitudes.size();
       i += (stride << 1)) { // avoid double swapping
    for (size_t j = 0; j < stride; ++j) {
      // get indices identical everywhere but targetQubit
      size_t idx0 = i + j;
      size_t idx1 = idx0 + stride;

      std::swap(amplitudes[idx0], amplitudes[idx1]); // swap amplitudes
    }
  }
}

void Statevector::applyY(size_t targetQubit) {
  size_t stride = 1ULL << targetQubit; // spacing

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx0 = i + j;
      size_t idx1 = idx0 + stride;

      // cache values
      std::complex<double> val0 = amplitudes[idx0];
      std::complex<double> val1 = amplitudes[idx1];

      amplitudes[idx0] = val1 * std::complex<double>(0, -1);
      amplitudes[idx1] = val0 * std::complex<double>(0, 1);
    }
  }
}

void Statevector::applyZ(size_t targetQubit) {
  size_t stride =
      1ULL << targetQubit; // spacing to find where target qubit is 1

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx1 = i + j + stride; // index where targetQubit is 1

      amplitudes[idx1] *= -1.0; // apply phase flip
    }
  }
}

void Statevector::applyH(size_t targetQubit) {
  size_t stride = 1ULL << targetQubit; // spacing to find where targetQubit is 1

  const double factor =
      1.0 / std::sqrt(2.0); // precalculate to avoid inside loop

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx0 = i + j;
      size_t idx1 = idx0 + stride;

      // cache values
      std::complex<double> val0 = amplitudes[idx0];
      std::complex<double> val1 = amplitudes[idx1];

      amplitudes[idx0] = (val0 + val1) * factor;
      amplitudes[idx1] = (val0 - val1) * factor;
    }
  }
}

void Statevector::applyCX(size_t controlQubit,
                          size_t targetQubit) { // TODO: optimize to remove if
  size_t stride = 1ULL << targetQubit;          // spacing

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx0 = i + j;
      size_t idx1 = idx0 + stride;

      if ((idx0 & (1ULL << controlQubit)) !=
          0) { // check if control qubit is 1 in the index
        std::swap(amplitudes[idx0], amplitudes[idx1]); // then apply swap
      }
    }
  }
}

size_t Statevector::numQubits() const {
  if (amplitudes.empty()) // handle edge case of 0 qubits
    return 0;

  return std::log2(amplitudes.size()); // base 2 logarithm gets num qubits
}
