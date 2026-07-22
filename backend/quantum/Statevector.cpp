#include "Statevector.hpp"

#include <cmath>
#include <random>
#include <utility>

void Statevector::initialize(size_t numQubits) {
  amplitudes.assign(1ULL << numQubits,
                    0); // resize to 2 amplitudes for each qubit, set all to 0
  amplitudes[0] = 1.0;  // |00...0>
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

void Statevector::applyS(size_t targetQubit) {
  size_t stride = 1ULL << targetQubit; // spacing to find where target qubit is 1

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx1 = i + j + stride; // index where targetQubit is 1

      amplitudes[idx1] *= std::complex<double>(0, 1); // apply phase i
    }
  }
}

void Statevector::applyT(size_t targetQubit) {
  size_t stride = 1ULL << targetQubit; // spacing to find where target qubit is 1

  const double sqrt2 = std::sqrt(2.0);
  const double factor = 1.0 / sqrt2; // 1/sqrt(2)

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx1 = i + j + stride; // index where targetQubit is 1

      amplitudes[idx1] *= std::complex<double>(factor, factor); // apply phase exp(i*pi/4)
    }
  }
}

void Statevector::applySDG(size_t targetQubit) {
  size_t stride = 1ULL << targetQubit; // spacing to find where target qubit is 1

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx1 = i + j + stride; // index where targetQubit is 1

      amplitudes[idx1] *= std::complex<double>(0, -1); // apply phase -i
    }
  }
}

void Statevector::applyTDG(size_t targetQubit) {
  size_t stride = 1ULL << targetQubit; // spacing to find where target qubit is 1

  const double sqrt2 = std::sqrt(2.0);
  const double factor = 1.0 / sqrt2; // 1/sqrt(2)

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx1 = i + j + stride; // index where targetQubit is 1

      amplitudes[idx1] *= std::complex<double>(factor, -factor); // apply phase exp(-i*pi/4)
    }
  }
}

void Statevector::applyRX(size_t targetQubit, double angle) {
  size_t stride = 1ULL << targetQubit; // spacing to find where target qubit is 1

  const double cos_a = std::cos(angle / 2.0);
  const double sin_a = std::sin(angle / 2.0);

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx0 = i + j;
      size_t idx1 = idx0 + stride;

      // cache values
      std::complex<double> val0 = amplitudes[idx0];
      std::complex<double> val1 = amplitudes[idx1];

      amplitudes[idx0] = val0 * cos_a - val1 * std::complex<double>(0, sin_a);
      amplitudes[idx1] = val1 * cos_a - val0 * std::complex<double>(0, sin_a);
    }
  }
}

void Statevector::applyRY(size_t targetQubit, double angle) {
  size_t stride = 1ULL << targetQubit; // spacing to find where target qubit is 1

  const double cos_a = std::cos(angle / 2.0);
  const double sin_a = std::sin(angle / 2.0);

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx0 = i + j;
      size_t idx1 = idx0 + stride;

      // cache values
      std::complex<double> val0 = amplitudes[idx0];
      std::complex<double> val1 = amplitudes[idx1];

      amplitudes[idx0] = val0 * cos_a - val1 * std::complex<double>(sin_a, 0);
      amplitudes[idx1] = val1 * cos_a + val0 * std::complex<double>(sin_a, 0);
    }
  }
}

void Statevector::applyRZ(size_t targetQubit, double angle) {
  size_t stride = 1ULL << targetQubit; // spacing to find where target qubit is 1

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx0 = i + j;
      size_t idx1 = idx0 + stride;

      // cache values
      std::complex<double> val0 = amplitudes[idx0];
      std::complex<double> val1 = amplitudes[idx1];

      double phase0 = -angle / 2.0;
      double phase1 = angle / 2.0;

      amplitudes[idx0] = val0 * std::exp(std::complex<double>(0, phase0));
      amplitudes[idx1] = val1 * std::exp(std::complex<double>(0, phase1));
    }
  }
}

void Statevector::applyPhase(size_t targetQubit, double angle) {
  size_t stride = 1ULL << targetQubit; // spacing to find where target qubit is 1

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx1 = i + j + stride; // index where targetQubit is 1

      amplitudes[idx1] *= std::exp(std::complex<double>(0, angle)); // apply global phase
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

bool Statevector::measure(size_t targetQubit) {
  size_t stride = 1ULL << targetQubit;
  double prob1 = 0.0; // probability of measuring 1

  for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
    for (size_t j = 0; j < stride; ++j) {
      size_t idx1 = i + j + stride;

      prob1 += std::norm(amplitudes[idx1]); // normalize to get probability
    }
  }

  static std::random_device rd;
  static std::mt19937 gen(rd()); // use marsen twister 19937
  std::uniform_real_distribution<double> dis(0.0, 1.0);
  double rand_val = dis(gen);

  bool outcome = (rand_val < prob1); // rand_val < prob1, then is 1, if rand_val
                                     // > prob 1, then is 0/false

  if (outcome) { // if is 1
    double norm_factor =
        1.0 /
        std::sqrt(
            prob1); // normalization factor to apply to indices where it was 1

    for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
      for (size_t j = 0; j < stride; ++j) {
        size_t idx0 = i + j;
        size_t idx1 = idx0 + stride;

        amplitudes[idx0] = 0.0; // zero out all the indices with 0 as result
        amplitudes[idx1] *= norm_factor; // renormalize
      }
    }
  } else { // if it is 0
    double norm_factor =
        1.0 /
        std::sqrt(
            1.0 -
            prob1); // normalization factor to apply to indices where it was 0

    for (size_t i = 0; i < amplitudes.size(); i += (stride << 1)) {
      for (size_t j = 0; j < stride; ++j) {
        size_t idx0 = i + j;
        size_t idx1 = idx0 + stride;

        amplitudes[idx1] = 0.0;          // zero out all 1 indices
        amplitudes[idx0] *= norm_factor; // renormalize
      }
    }
  }
  return outcome;
}

size_t Statevector::numQubits() const {
  if (amplitudes.empty()) // handle edge case of 0 qubits
    return 0;

  return std::log2(amplitudes.size()); // base 2 logarithm gets num qubits
}
