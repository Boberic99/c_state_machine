This repository contains a small, production-style finite state machine (FSM)
library written in ISO C. The project focuses on correctness, explicit error
handling, and ease of review rather than feature completeness.

## Steps to build FSM library on Linux machine:

    1. Open terminal and navigate to cloned repository.
    2. Execute command "make all".
    3. Execute command "make example"
    4. Execute command "make test"
        - "TESTS PASSED" will be printed in the command line if everything is valid.

## Object files can be found in "obj" directory and libfsm.a can be found in "lib" directory.

## Test and example executables can be found in "test" and "example" directories respectively.

## Design decisions
- FSM does not allocate memory internally
- Transition table is immutable and caller-owned
- Actions run before state mutation
- State is updated only on successful action

