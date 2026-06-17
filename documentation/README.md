# Quell
A functional programming language that integrates classical computation with a quantum execution backend.

---

## Overview
Quell is a programming language designed to unify classical control flow and quantum computation in a single functional language. Programs compile into a low-level intermediate representation (`.q`) executed by a custom virtual machine that includes both a classical runtime and a quantum simulator.

---

## Preview
(No compiler implemented yet)

---

## Try it
(No public runtime yet)

---

## Features
- Functional language with expression-based syntax
- Classical and quantum computation in one runtime
- Custom bytecode-style intermediate representation (`.q`)
- Measurement and reset operations integrated into execution model
- Classical VM supporting arithmetic, branching, and function calls
- Register-based quantum memory model

---

## Quick start
(Not yet available)

---

## How Quell works
Quell is compiled in multiple stages

Quell source (`.ql`)
        ↓
Parser + AST
        ↓
Semantic analysis
        ↓
Lowering pass
        ↓
Intermediate representation (`.q`)
        ↓
Quell VM (classical + quantum backend)

### Quantum execution model
Quell uses a **register-based quantum system**:
- Qubits exist inside registers
- A register may contain one or more qubits
- Single qubits are either:
    - a reference to a register element
    - or an independently allocated single-qubit register

### Backend instruction set
The Quell VM executes a low-level instruction set supporting both classical and quantum operations.

Quantum instructions:
- I
- H, X, Y, Z
- S, SDG
- T, TDG
- RX, RY, RZ
- PHASE
- CX

Higher-level gates such as:
- CZ
- SWAP
are lowered into CX + single-qubit transformations

Special quantum operations:
- MEASURE
- RESET

Classical VM:
- Arithmetic: ADD, SUB, MUL, DIV
- Comparisons: EQ, NE, LT, LE, GT, GE
- Control flow: JMP, conditional jumps
- Function System: CALL, RET
- Stack operations: PUSH, POP

---

## Design notes
- Qubits are not freely copyable values; they are references to registers
- Measurement and reset are explicity VM operations rather than gates
- The backend is designed to support lowering from a higher-level functional language rather than direct instruction authoring

---

## Status
Early development stage.

Current progress:
- Grammar defined
- Instruction set designed
- Backend architecture in progress
- Compiler not yet implemented

---

## What's next
- Implement `.q` virtual machine execution
- Build parser and AST
- Implement lowering from Quell -> IR
- Add dynamic allocation system for qubits/registers
- Begin type system and semantic checks

---

## Notes
This project is experimental and changing a lot. The architecture is expected to change as the compiler and backend are implemented.
