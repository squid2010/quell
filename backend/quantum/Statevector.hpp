#ifndef STATEVECTOR_HPP
#define STATEVECTOR_HPP

#include <complex>
#include <cstddef>
#include <vector>

class Statevector { // actually stores the full states of all the qubits
private:
  std::vector<std::complex<double>>
      amplitudes; // just a list of probability amplitudes

public:
  void initialize(size_t numQubits); // initialize all amplitudes to 0

  void applyX(size_t targetQubit);                       // apply Pauli X gate
  void applyY(size_t targetQubit);                       // apply Pauli Y gate
  void applyZ(size_t targetQubit);                       // apply Pauli Z gate
  void applyH(size_t targetQubit);                       // apply Hadamard gate
  void applyS(size_t targetQubit);                       // apply S gate
  void applyT(size_t targetQubit);                       // apply T gate
  void applySDG(size_t targetQubit);                     // apply S† gate
  void applyTDG(size_t targetQubit);                     // apply T† gate
  void applyRX(size_t targetQubit, double angle);        // apply RX gate
  void applyRY(size_t targetQubit, double angle);        // apply RY gate
  void applyRZ(size_t targetQubit, double angle);        // apply RZ gate
  void applyPhase(size_t targetQubit, double angle);     // apply phase gate
  void applyCX(size_t controlQubit, size_t targetQubit); // apply CX gate

  bool measure(size_t targetQubit);

  size_t numQubits() const;
};

#endif
