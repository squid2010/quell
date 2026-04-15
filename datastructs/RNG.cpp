#include "RNG.hpp"
#include <stdexcept>

RNG::RNG() {             // random seed
  std::random_device rd; // generate random seed
  engine.seed(rd());
}

RNG::RNG(uint64_t seed) { // fixed seed
  engine.seed(seed);
}

void RNG::seed(uint64_t seed) { // reseed
  engine.seed(seed);
}

// Uniform Distributions
double RNG::uniform() { // [0, 1)
  std::uniform_real_distribution<double> dist(0.0,
                                              1.0); // generate distribution
  return dist(engine); // pass engine to distribution
}

double RNG::uniform(double a, double b) {            // [a, b)
  std::uniform_real_distribution<double> dist(a, b); // generate distribution
  return dist(engine); // pass engine to distribution
}

size_t RNG::uniform_index(size_t max) { // integer in [0, max - 1]
  if (max <= 0)                         // can't have a range of [0, -x] i think
    throw std::invalid_argument("max must be > 0");

  std::uniform_int_distribution<size_t> dist(0,
                                             max - 1); // generate distribution
  return dist(engine); // pass engine to distribution
}

double RNG::normal(double mean, double stddev) {       // normal distribution
  std::normal_distribution<double> dist(mean, stddev); // generate distribution
  return dist(engine); // pass engine to distribution
}

size_t RNG::sample(const DynamicArray<double> &probabilities) {
  if (probabilities.get_size() == 0)
    throw std::invalid_argument("Empty probability array");

  std::discrete_distribution<size_t> dist(
      &probabilities[0], &probabilities[0] + probabilities.get_size());
  return dist(engine);
}
