# Deadlock Management Module

## Project Description

The Deadlock Management Module is part of the Week 4 Process Scheduling and Resource Management project. It focuses on handling resource allocation, checking system safety, detecting deadlocks, processing resource requests, and recovering from deadlock situations.

The module uses shared project data structures defined in `common.h` to work with process information, resource availability, allocation matrices, maximum resource requirements, and remaining resource needs.

## Objectives

- Determine whether a system is in a safe or unsafe state.
- Implement Banker’s Algorithm to find a safe sequence of processes.
- Detect deadlocks using outstanding resource requests and allocated resources.
- Process resource requests while ensuring the system remains in a safe state.
- Recover from deadlock by terminating a deadlocked process and releasing its allocated resources.
- Test the algorithms using independent test cases.

## My Role and Contribution

My responsibility is to implement and test the deadlock management functionality.

The files developed for this module are:

- `deadlock.c` — contains the implementations of the deadlock management algorithms.
- `deadlock.h` — declares the functions provided by the module.
- `tests/tests.c` — contains test cases for verifying the implemented functionality.
- `tests/test_results.md` — documents the compilation output, test cases, results, and conclusion.

## Algorithms Implemented

### 1. Banker’s Algorithm

Checks whether the current system state is safe by determining whether processes can finish in an order that allows their allocated resources to be released. The resulting safe sequence is stored in the shared system state.

### 2. Deadlock Detection

Examines available resources, process allocations, and outstanding resource requests to identify processes that cannot complete under the current resource conditions.

### 3. Resource Request Handling

Validates a process's resource request, checks resource availability, and tentatively updates the allocation state. The request is retained only if the resulting state is safe; otherwise, the allocation changes are rolled back.

### 4. Deadlock Recovery

Selects a detected deadlocked process for termination, releases its allocated resources, updates the system state, and checks whether the deadlock remains.

## Project Structure

```text
shashwath/
├── deadlock.c
├── deadlock.h
├── README.md
└── tests/
    ├── tests.c
    └── test_results.md
```

The module uses the shared `common.h` file maintained by the team rather than defining a separate system-state structure.

## Compilation and Execution

Run the following commands from the `week3/src` directory in WSL:

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 \
    shashwath/deadlock.c shashwath/tests/tests.c \
    -o shashwath/test_deadlock

./shashwath/test_deadlock
```

## Testing

The test suite currently covers five scenarios:

1. Banker’s Algorithm with a safe state.
2. Banker’s Algorithm with an unsafe state.
3. Detection of two deadlocked processes.
4. Recovery by terminating a deadlocked process.
5. Granting a safe resource request.

All five test cases passed during standalone execution.

Refer to `tests/test_results.md` for the recorded compilation and testing results.

## Conclusion

The Deadlock Management Module implements the core algorithms required for safe-state checking, deadlock detection, resource-request handling, and deadlock recovery. The module has passed its current standalone tests and is intended to integrate with the shared data structures and other components of the team project.

Full-project integration testing remains necessary to verify compatibility with the other team members' modules.
