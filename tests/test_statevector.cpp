#include "../datastructs/Complex.hpp"
#include "../datastructs/Matrix.hpp"
#include "../datastructs/RNG.hpp"
#include "../datastructs/StateVector.hpp"
#include <cmath>
#include <gtest/gtest.h>

static const double EPS = 1e-9;

TEST(StatevectorTest, DefaultConstructorCreatesZeroState) {
  Statevector psi(3); // 3 qubits → dimension 8

  EXPECT_EQ(psi.size(), 8);
  EXPECT_EQ(psi.qubits(), 3);

  // |000>
  EXPECT_NEAR(psi[0].get_real(), 1.0, EPS);
  EXPECT_NEAR(psi[0].get_imag(), 0.0, EPS);

  for (size_t i = 1; i < psi.size(); ++i) {
    EXPECT_NEAR(psi[i].get_real(), 0.0, EPS);
    EXPECT_NEAR(psi[i].get_imag(), 0.0, EPS);
  }
}

TEST(StatevectorTest, CustomAmplitudeConstructor) {
  DynamicArray<Complex> amps;
  amps.push_back(Complex(1, 0));
  amps.push_back(Complex(0, 0));

  Statevector psi(amps, 1);

  EXPECT_EQ(psi.size(), 2);
  EXPECT_NEAR(psi[0].get_real(), 1.0, EPS);
  EXPECT_NEAR(psi[1].get_real(), 0.0, EPS);
}

TEST(StatevectorTest, Normalize) {
  DynamicArray<Complex> amps;
  amps.push_back(Complex(2, 0));
  amps.push_back(Complex(0, 0));

  Statevector psi(amps, 1);
  psi.normalize();

  EXPECT_NEAR(psi[0].get_real(), 1.0, EPS);
  EXPECT_NEAR(psi[1].get_real(), 0.0, EPS);
}

TEST(StatevectorTest, InnerProductSelfEqualsOne) {
  Statevector psi(2); // |00>
  Complex result = psi.inner_product(psi);

  EXPECT_NEAR(result.get_real(), 1.0, EPS);
  EXPECT_NEAR(result.get_imag(), 0.0, EPS);
}

TEST(StatevectorTest, InnerProductOrthogonalStates) {
  Statevector psi(1); // |0>

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  psi.apply_gate(X, 0); // now |1>

  Statevector zero(1); // |0>

  Complex result = psi.inner_product(zero);

  EXPECT_NEAR(result.get_real(), 0.0, EPS);
  EXPECT_NEAR(result.get_imag(), 0.0, EPS);
}

TEST(StatevectorTest, ApplyPauliX) {
  Statevector psi(1); // |0>

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  psi.apply_gate(X, 0);

  EXPECT_NEAR(psi[0].get_real(), 0.0, EPS);
  EXPECT_NEAR(psi[1].get_real(), 1.0, EPS);
}

TEST(StatevectorTest, ApplyHadamard) {
  Statevector psi(1); // |0>

  double inv_sqrt2 = 1.0 / std::sqrt(2.0);

  Matrix H(Complex(inv_sqrt2, 0), Complex(inv_sqrt2, 0), Complex(inv_sqrt2, 0),
           Complex(-inv_sqrt2, 0));

  psi.apply_gate(H, 0);

  EXPECT_NEAR(psi[0].get_real(), inv_sqrt2, EPS);
  EXPECT_NEAR(psi[1].get_real(), inv_sqrt2, EPS);
}

TEST(StatevectorTest, ApplyGateOnSpecificQubit) {
  Statevector psi(2); // |00>

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  // Apply X to qubit 1 (second qubit)
  psi.apply_gate(X, 1);

  // Expect |10> (binary index 2)
  EXPECT_NEAR(psi[2].get_real(), 1.0, EPS);

  for (size_t i = 0; i < psi.size(); ++i) {
    if (i != 2)
      EXPECT_NEAR(psi[i].get_real(), 0.0, EPS);
  }
}

TEST(StatevectorTest, InnerProductDimensionMismatchThrows) {
  Statevector psi1(1);
  Statevector psi2(2);

  EXPECT_THROW(psi1.inner_product(psi2), std::runtime_error);
}

TEST(StatevectorTest, InvalidQubitIndexThrows) {
  Statevector psi(1);

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  EXPECT_THROW(psi.apply_gate(X, 2), std::runtime_error);
}

TEST(StatevectorTest, MeasureBasisStateDeterministic) {
  RNG rng(42);

  Statevector psi(2); // |00>

  size_t result = psi.measure(rng);

  EXPECT_EQ(result, 0u);

  // State remains |00>
  EXPECT_NEAR(psi[0].get_real(), 1.0, EPS);
  for (size_t i = 1; i < psi.size(); ++i)
    EXPECT_NEAR(psi[i].get_real(), 0.0, EPS);
}

TEST(StatevectorTest, MeasureCollapsesState) {
  RNG rng(42);

  Statevector psi(1);

  double inv_sqrt2 = 1.0 / std::sqrt(2.0);
  Matrix H(Complex(inv_sqrt2, 0), Complex(inv_sqrt2, 0), Complex(inv_sqrt2, 0),
           Complex(-inv_sqrt2, 0));

  psi.apply_gate(H, 0);

  size_t result = psi.measure(rng);

  // After measurement, state must be pure basis state
  for (size_t i = 0; i < psi.size(); ++i) {
    if (i == result)
      EXPECT_NEAR(psi[i].abs(), 1.0, EPS);
    else
      EXPECT_NEAR(psi[i].abs(), 0.0, EPS);
  }
}

TEST(StatevectorTest, MeasureSuperpositionStatisticalCheck) {
  RNG rng(123);

  const int samples = 100000;
  int count0 = 0;
  int count1 = 0;

  for (int i = 0; i < samples; ++i) {
    Statevector psi(1);

    double inv_sqrt2 = 1.0 / std::sqrt(2.0);
    Matrix H(Complex(inv_sqrt2, 0), Complex(inv_sqrt2, 0),
             Complex(inv_sqrt2, 0), Complex(-inv_sqrt2, 0));

    psi.apply_gate(H, 0);

    size_t result = psi.measure(rng);

    if (result == 0)
      ++count0;
    else if (result == 1)
      ++count1;
  }

  double freq0 = static_cast<double>(count0) / samples;
  double freq1 = static_cast<double>(count1) / samples;

  EXPECT_NEAR(freq0, 0.5, 0.01);
  EXPECT_NEAR(freq1, 0.5, 0.01);
}
