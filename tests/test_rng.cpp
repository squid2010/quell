#include "../datastructs/DynamicArray.hpp"
#include "../datastructs/RNG.hpp"
#include <gtest/gtest.h>

static const double EPS = 1e-9;

TEST(RNGTest, DeterministicSeedingProducesSameSequence) {
  RNG rng1(12345);
  RNG rng2(12345);

  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR(rng1.uniform(), rng2.uniform(), EPS);
  }
}

TEST(RNGTest, UniformInUnitInterval) {
  RNG rng(42);

  for (int i = 0; i < 1000; ++i) {
    double value = rng.uniform();
    EXPECT_GE(value, 0.0);
    EXPECT_LT(value, 1.0);
  }
}

TEST(RNGTest, UniformInCustomRange) {
  RNG rng(42);

  for (int i = 0; i < 1000; ++i) {
    double value = rng.uniform(-2.0, 3.0);
    EXPECT_GE(value, -2.0);
    EXPECT_LT(value, 3.0);
  }
}

TEST(RNGTest, UniformIndexWithinBounds) {
  RNG rng(42);
  size_t max = 10;

  for (int i = 0; i < 1000; ++i) {
    size_t idx = rng.uniform_index(max);
    EXPECT_LT(idx, max);
  }
}

TEST(RNGTest, UniformIndexZeroThrows) {
  RNG rng(42);
  EXPECT_THROW(rng.uniform_index(0), std::invalid_argument);
}

TEST(RNGTest, NormalDistributionRoughMeanCheck) {
  RNG rng(42);

  const int samples = 100000;
  double sum = 0.0;

  for (int i = 0; i < samples; ++i)
    sum += rng.normal(0.0, 1.0);

  double mean = sum / samples;

  // With 100k samples, mean should be close to 0
  EXPECT_NEAR(mean, 0.0, 0.01);
}

TEST(RNGTest, DiscreteSamplingDeterministicSingleOutcome) {
  RNG rng(42);

  DynamicArray<double> probs;
  probs.push_back(0.0);
  probs.push_back(1.0);
  probs.push_back(0.0);

  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(rng.sample(probs), 1u);
  }
}

TEST(RNGTest, DiscreteSamplingRoughDistributionCheck) {
  RNG rng(123);

  DynamicArray<double> probs;
  probs.push_back(0.25);
  probs.push_back(0.75);

  const int samples = 100000;
  int count0 = 0;
  int count1 = 0;

  for (int i = 0; i < samples; ++i) {
    size_t result = rng.sample(probs);
    if (result == 0)
      ++count0;
    else if (result == 1)
      ++count1;
  }

  double freq0 = static_cast<double>(count0) / samples;
  double freq1 = static_cast<double>(count1) / samples;

  EXPECT_NEAR(freq0, 0.25, 0.01);
  EXPECT_NEAR(freq1, 0.75, 0.01);
}

TEST(RNGTest, SampleEmptyThrows) {
  RNG rng(42);
  DynamicArray<double> probs;
  EXPECT_THROW(rng.sample(probs), std::invalid_argument);
}
