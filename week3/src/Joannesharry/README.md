# Process and Resource Management Module

## 1. Overview

This module is part of the Operating Systems Deadlock Simulation System. It manages processes, resources, resource allocation, maximum resource requirements, available resources, and remaining resource needs.

The module uses the shared `SystemState` structure defined in `../Sameeha/common.h`.

## 2. Files

- `process.c` – Contains the implementation of process and resource management functions.
- `process.h` – Contains function declarations.
- `tests/test_process.c` – Contains the test program.
- `test_cases.txt` – Describes the test cases and expected results.

## 3. Main Functions

- `initialize_processes()` – Initializes process IDs and names.
- `initialize_resources()` – Initializes resource IDs and names.
- `set_total_resources()` – Sets the total number of instances of a resource.
- `set_allocation()` – Assigns resources to processes.
- `set_maximum()` – Sets the maximum resource requirements of processes.
- `calculate_need()` – Calculates the remaining resource requirements.
- `calculate_available()` – Calculates the available resources.
- `validate_request()` – Checks whether a resource request is valid.
- `display_processes()` – Displays process information.
- `display_resources()` – Displays resource information and matrices.

## 4. Formulas

**Need = Maximum − Allocation**

**Available = Total Resources − Allocated Resources**

## 5. Example

The test program uses three processes and two resource types.

### Total Resources

| Resource | Total |
|----------|-------|
| R0       | 4     |
| R1       | 3     |

### Allocation Matrix

| Process | R0 | R1 |
|---------|----|----|
| P0      | 1  | 0  |
| P1      | 0  | 1  |
| P2      | 1  | 1  |

### Maximum Matrix

| Process | R0 | R1 |
|---------|----|----|
| P0      | 2  | 1  |
| P1      | 1  | 2  |
| P2      | 2  | 2  |

### Expected Results

- P0 Need: [1, 1]
- P1 Need: [1, 1]
- P2 Need: [1, 1]
- Available Resources: [2, 1]

## 6. Compilation

Run the following command from the `Joannes` directory:

    gcc -Wall -Wextra -std=c11 process.c tests/test_process.c -o test_process

## 7. Execution

Run the test program using:

    ./test_process

If all tests pass, the program should display:

    All process and resource tests passed!

## 8. Conclusion

The module provides basic process and resource management functionality for the deadlock simulation project. It calculates resource needs and availability and validates resource requests before further processing by the system.