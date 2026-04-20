#include "../datastructs/Circuit.hpp"
#include "../datastructs/Complex.hpp"
#include "../datastructs/Matrix.hpp"
#include "../datastructs/RNG.hpp"
#include "../datastructs/StateVector.hpp"

#include <cmath>
#include <gtest/gtest.h>

static const double EPS = 1e-9;

TEST(CircuitTest, DefaultConstructorCreatesZeroState) {
  Circuit circuit(3);

  EXPECT_EQ(circuit.qubits(), 3u);
  EXPECT_EQ(circuit.gate_count(), 0u);

  Statevector result = circuit.execute();

  EXPECT_EQ(result.size(), 8u);
  EXPECT_NEAR(result[0].get_real(), 1.0, EPS);

  for (size_t i = 1; i < result.size(); ++i)
    EXPECT_NEAR(result[i].get_real(), 0.0, EPS);
}

TEST(CircuitTest, AddGateIncreasesGateCount) {
  Circuit circuit(1);

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  circuit.add_gate(X, 0);

  EXPECT_EQ(circuit.gate_count(), 1u);
}

TEST(CircuitTest, SinglePauliXExecution) {
  Circuit circuit(1);

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  circuit.add_gate(X, 0);

  Statevector result = circuit.execute();

  EXPECT_NEAR(result[0].get_real(), 0.0, EPS);
  EXPECT_NEAR(result[1].get_real(), 1.0, EPS);
}

TEST(CircuitTest, SequentialGates) {
  Circuit circuit(1);

  double inv_sqrt2 = 1.0 / std::sqrt(2.0);

  Matrix H(Complex(inv_sqrt2, 0), Complex(inv_sqrt2, 0), Complex(inv_sqrt2, 0),
           Complex(-inv_sqrt2, 0));

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  circuit.add_gate(H, 0);
  circuit.add_gate(X, 0);

  Statevector result = circuit.execute();

  // XH|0> = X(|+>) = |+>
  EXPECT_NEAR(result[0].get_real(), inv_sqrt2, EPS);
  EXPECT_NEAR(result[1].get_real(), inv_sqrt2, EPS);
}

TEST(CircuitTest, GateOnSpecificQubit) {
  Circuit circuit(2);

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  circuit.add_gate(X, 1);

  Statevector result = circuit.execute();

  // |00> -> apply X to qubit 1 -> |10> (index 2)
  EXPECT_NEAR(result[2].get_real(), 1.0, EPS);

  for (size_t i = 0; i < result.size(); ++i) {
    if (i != 2)
      EXPECT_NEAR(result[i].get_real(), 0.0, EPS);
  }
}

TEST(CircuitTest, ExecuteAndMeasureDeterministic) {
  RNG rng(42);

  Circuit circuit(1);

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  circuit.add_gate(X, 0);

  size_t result = circuit.execute_and_measure(rng);

  EXPECT_EQ(result, 1u);
}

TEST(CircuitTest, ExecuteAndMeasureStatistical) {
  RNG rng(123);

  const int samples = 100000;
  int count0 = 0;
  int count1 = 0;

  double inv_sqrt2 = 1.0 / std::sqrt(2.0);

  Matrix H(Complex(inv_sqrt2, 0), Complex(inv_sqrt2, 0), Complex(inv_sqrt2, 0),
           Complex(-inv_sqrt2, 0));

  for (int i = 0; i < samples; ++i) {
    Circuit circuit(1);
    circuit.add_gate(H, 0);

    size_t result = circuit.execute_and_measure(rng);

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

TEST(CircuitTest, InvalidQubitIndexThrows) {
  Circuit circuit(1);

  Matrix X(Complex(0, 0), Complex(1, 0), Complex(1, 0), Complex(0, 0));

  EXPECT_THROW(circuit.add_gate(X, 2), std::runtime_error);
}
