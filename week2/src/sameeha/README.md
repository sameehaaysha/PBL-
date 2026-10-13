# Process Scheduling Simulator – Main Integration Module

## 1. Project Overview

The Process Scheduling Simulator is a C-based project designed to demonstrate process management and CPU scheduling concepts. This module provides the main program structure and integrates process-related components to support the execution of the simulator.

## 2. Role and Responsibilities

**Role:** Main Integration and Process Management

Responsibilities:

* Developing and maintaining the main program entry point.
* Integrating process-related components.
* Coordinating program execution.
* Using shared data structures and function declarations.
* Supporting compilation, testing, and debugging of the module.

## 3. Files and Their Responsibilities

| File Name   | Description                                                      |
| ----------- | ---------------------------------------------------------------- |
| `Common.h`  | Defines shared structures and constants used across the project. |
| `Process.h` | Contains process-related function declarations.                  |
| `Process.c` | Implements process-related operations.                           |
| `Main.c`    | Provides the main entry point and coordinates program execution. |

## 4. Technologies Used

* **Programming Language:** C
* **Compiler:** GCC
* **Operating System:** Ubuntu/Linux


## 5. Prerequisites

Before compiling the module, ensure that:

* GCC is installed.
* All required source and header files are available.
* The terminal is opened in the project source directory.
* Any additional source files required by the integration are included.

## 6. Compilation and Execution

Compile the module using GCC:

```bash
gcc Main.c Process.c -o simulator
```

Execute the compiled program:

```bash
./simulator
```

**Note:** If the simulator depends on additional scheduling algorithm source files, include those files in the compilation command.

## 7. Input and Output

The program processes the input required by the implemented process-management functionality and displays the corresponding results.

The exact input format and output depend on the implementation of the source files.

## 8. Integration Details

The main module acts as the entry point for the program. `Main.c` coordinates the required operations, `Process.c` provides process-related functionality, and the header files supply shared structures and function declarations.

This module is intended to work with the other components of the Process Scheduling Simulator.

## 9. Testing and Validation

The module can be validated by:

* Compiling the source files using GCC.
* Checking for compilation errors and warnings.
* Running the generated executable.
* Verifying process-related operations and displayed results.
* Checking compatibility with the integrated project modules.

## 10. Expected Outcome

The module provides a central entry point for the simulator and supports the integration of process-management functionality with the overall project.

## 11. Conclusion

The Main Integration Module organizes the process-related components and provides the foundation for executing the Process Scheduling Simulator. It contributes to a modular structure that supports testing, maintenance, and future development.
