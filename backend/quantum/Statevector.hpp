#ifndef STATEVECTOR_HPP
#define STATEVECTOR_HPP

#include <complex>
#include <vector>

class Statevector { // actually stores the full states of all the qubits
private:
  std::vector<std::complex<double>>
      amplitudes; // just a list of probability amplitudes

public:
  void initialize(size_t numQubits);
};

#endif
