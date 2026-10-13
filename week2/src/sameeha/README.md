# Process Scheduling Simulator

## 1. Overview

This module is responsible for integrating the process management components of the Process Scheduling Simulator. It provides the main entry point for program execution and coordinates the required process-related operations.

## 2. Responsibilities

* Integrating process management components.
* Coordinating program execution through the main function.
* Managing process-related operations.
* Connecting shared data structures and function declarations.
* Supporting the execution and testing of the simulator.

## 3. Files Included

| File Name   | Description                                                       |
| ----------- | ----------------------------------------------------------------- |
| `Common.h`  | Defines shared data structures and constants used across modules. |
| `Process.h` | Contains process-related function declarations.                   |
| `Process.c` | Implements process-related operations.                            |
| `Main.c`    | Serves as the main entry point and coordinates program execution. |

## 4. Technologies Used

* **Programming Language:** C
* **Compiler:** GCC
* **Operating Environment:** Ubuntu/Linux

## 5. Compilation and Execution

Compile the source files using GCC:

```bash
gcc Main.c Process.c -o simulator
```

Run the executable:

```bash
./simulator
```

## 6. Expected Outcome

The module provides a central entry point for the simulator and supports the integration of process management components with the overall scheduling system.

## 7. Conclusion

The integration module contributes to the overall Process Scheduling Simulator by organizing process-related functionality and coordinating program execution.
