#ifndef RNG_HPP
#define RNG_HPP

#include "DynamicArray.hpp"
#include <cstddef>
#include <random>

class RNG {
private:
  std::mt19937_64 engine; // 64-bit Mersenne Twister

public:
  // Constructors
  RNG();                       // random seed
  explicit RNG(uint64_t seed); // fixed seed

  void seed(uint64_t seed); // reseed

  // uniform distributions
  double uniform();                   // [0, 1)
  double uniform(double a, double b); // [a, b)
  size_t uniform_index(size_t max);   // integer in [0, max -1]

  double normal(double mean, double stddev); // normal distribution

  size_t sample(const DynamicArray<double> &probabilities); // discrete sampling
};

#endif
