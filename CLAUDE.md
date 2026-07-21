# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Quell is a functional programming language that integrates classical computation with a quantum execution backend. The project consists of:

- A custom virtual machine (VM) that executes both classical and quantum instructions
- Quantum simulation capabilities using statevector representation
- Classical control flow operations
- A register-based quantum memory model

## Architecture

The codebase is structured around three main components:

1. **Backend VM** (`backend/vm/`):
   - `VM.hpp/cpp`: Main virtual machine execution engine that interprets and executes instructions
   - `Instruction.hpp`: Defines the instruction set including both classical and quantum operations
   - `Program.hpp`: Represents a program as a sequence of instructions

2. **Quantum Simulation** (`backend/quantum/`):
   - `Statevector.hpp/cpp`: Implements the quantum state representation and quantum gate operations
   - `QuantumRegister.hpp/cpp`: Manages quantum registers and qubit addressing

3. **Classical Operations** (`backend/classical/`):
   - `ClassicalRegister.hpp/cpp`: Handles classical register operations for storing classical bits

## Build System

The project uses CMake as the build system:

```bash
mkdir build && cd build
cmake ..
make
```

To run tests:
```bash
cd build
make test
# or
ctest
```

## Key Features Implemented

- Quantum gate operations: I, X, Y, Z, H, CX (controlled-X)
- Measurement and reset operations
- Classical VM operations: arithmetic, comparisons, control flow
- Register-based quantum memory model
- Basic instruction set architecture with both immediate and register-based addressing

## Development Workflow

When developing in this codebase:
1. Add new instructions to `Instruction.hpp` 
2. Implement instruction handling in `VM.cpp`
3. Extend quantum operations in `Statevector.hpp/cpp`
4. Run tests using `ctest` in the build directory
5. Follow existing patterns for test structure and naming conventions

## Testing Approach

Tests are written using Google Test framework:
- Tests for individual instructions in `tests/backend/vm/test_instruction.cpp`
- Tests for VM execution in `tests/backend/vm/test_vm.cpp`

The VM test includes a Bell state correlation test that demonstrates quantum entanglement properties.