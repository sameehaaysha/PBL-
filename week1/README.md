# Week 1 – Multi-Process Simulator & IPC

## 1. Project Overview

The Week 1 project is a multi-process simulator developed in C. The main objective is to simulate basic computer system components and demonstrate communication between different processes using **Inter-Process Communication (IPC)**.

The simulator contains separate modules for the CPU, Memory, Stack, Queue, User Interface, Core, and Logger.

The processes communicate using **POSIX Message Queues**.

---

## 2. Objectives

* Understand the concept of multi-process systems.
* Implement basic CPU operations.
* Implement memory read and write operations.
* Implement stack operations.
* Implement queue operations.
* Create a simple user interface for entering commands.
* Implement a Core process to process commands.
* Implement a Logger process to record execution results.
* Use POSIX Message Queues for Inter-Process Communication.
* Integrate all components into one working simulator.

---

## 3. Project Structure

```text
Week1/
└── src/
    ├── core/
    │   └── core.c
    │
    ├── logger/
    │   └── logger.c
    │
    ├── ui/
    │   └── ui.c
    │
    └── ipc/
        ├── common.h
        └── ipc.c
```

---

## 4. Modules

### CPU Module

The CPU module performs basic arithmetic and control operations.

Supported instructions include:

* LOAD
* ADD
* SUB
* MUL
* DIV
* HALT

The CPU maintains:

* Accumulator
* Program Counter
* Running status

---

### Memory Module

The memory module provides storage and retrieval of integer values.

Operations:

* STORE
* READ

The simulator uses a fixed-size memory array.

Example:

```text
STORE 5 100
READ 5
```

Result:

```text
Memory[5] = 100
```

---

### Stack Module

The stack follows the **LIFO (Last In, First Out)** principle.

Operations:

* PUSH
* POP
* PEEK

Example:

```text
PUSH 50
PEEK
POP
```

---

### Queue Module

The queue follows the **FIFO (First In, First Out)** principle.

Operations:

* ENQUEUE
* DEQUEUE
* QPEEK

Example:

```text
ENQUEUE 25
QPEEK
DEQUEUE
```

---

### UI Module

The UI provides an interface for entering commands.

The UI sends commands to the Core process through the POSIX message queue:

```text
UI → UI_TO_CORE → Core
```

The UI also handles the EXIT command to request shutdown.

---

### Core Module

The Core acts as the main processing component.

It:

* Receives commands from the UI.
* Identifies the requested operation.
* Executes CPU, Memory, Stack, and Queue operations.
* Sends results back to the UI.
* Sends execution information to the Logger.

Communication:

```text
UI → Core
Core → UI
Core → Logger
```

---

### Logger Module

The Logger receives messages from the Core and records them in log files.

Two types of logs are supported:

```text
logs/execution.log
logs/error.log
```

The logger records the date, time, and message.

---

## 5. IPC Integration

The project uses **POSIX Message Queues** for communication between processes.

Three message queues are used:

```text
/ui_to_core
/core_to_ui
/core_to_log
```

Communication flow:

```text
             +-------------+
             |     UI      |
             +-------------+
                    |
                    | UI_TO_CORE
                    ↓
             +-------------+
             |    CORE     |
             +-------------+
               |         |
               |         |
       CORE_TO_UI     CORE_TO_LOG
               ↓         ↓
             UI       LOGGER
```

---

## 6. Common Header – `common.h`

The `common.h` file contains the definitions shared by the IPC-related modules.

It defines:

* Message queue names
* Maximum message size
* Message types
* Common `Message` structure

Message types include:

```text
MSG_COMMAND
MSG_RESULT
MSG_ERROR
MSG_SHUTDOWN
```

This ensures that the UI, Core, Logger, and IPC manager use the same communication format.

---

## 7. IPC Manager – `ipc.c`

The `ipc.c` file performs the main process integration.

Its responsibilities are:

1. Create the POSIX message queues.
2. Create processes using `fork()`.
3. Start the UI process.
4. Start the Core process.
5. Start the Logger process.
6. Wait for all processes to finish.
7. Close the message queues.
8. Remove the message queues during cleanup.

The process startup flow is:

```text
ipc.c
 ├──→ UI
 ├──→ Core
 └──→ Logger
```

This acts as the final glue that connects the different components of the simulator.

---

## 8. Error Handling

The simulator handles common errors such as:

* Invalid memory address
* Empty stack
* Empty queue
* Stack overflow
* Queue overflow
* Division by zero
* Invalid instructions
* Message queue errors

Error messages are sent to the appropriate process and can be recorded by the Logger.

---

## 9. Testing Performed

The integrated simulator was tested using the following commands.

### CPU Testing

```text
LOAD 10
ADD 5
```

Expected result:

```text
ACC = 10
ACC = 15
```

### Memory Testing

```text
STORE 5 100
READ 5
```

Expected result:

```text
Memory[5] = 100
Memory[5] = 100
```

### Stack Testing

```text
PUSH 50
PEEK
POP
```

### Queue Testing

```text
ENQUEUE 25
QPEEK
DEQUEUE
```

### Shutdown Testing

```text
EXIT
```

The processes terminate and the IPC resources are cleaned up.

---

## 10. Logging Test

Execution messages were successfully sent from Core to Logger.

Example:

```text
Logged: Instruction executed: LOAD 10
```

The messages are stored in:

```text
logs/execution.log
```

---

## 11. Technologies Used

* C Programming
* Linux / Ubuntu
* POSIX Message Queues
* `fork()`
* `execl()`
* `mq_open()`
* `mq_send()`
* `mq_receive()`
* `waitpid()`
* GCC

---

## 12. Team Contributions

### CPU Module

Implemented CPU instructions and arithmetic operations.

### Memory Module

Implemented memory read and write operations.

### Stack Module

Implemented stack operations using LIFO.

### Queue Module

Implemented queue operations using FIFO.

### UI Module

Implemented the user interface for entering simulator commands.

### Logger Module

Implemented logging of execution and error messages.

### IPC Integration – Member 4 / Team Leader

* Designed the common IPC definitions.
* Created `common.h`.
* Created `ipc.c`.
* Created and managed POSIX message queues.
* Integrated the UI, Core, and Logger processes.
* Tested communication between the processes.
* Performed final integration testing.

---

## 13. Final Result

The Week 1 simulator demonstrates a working multi-process architecture where independent components communicate using POSIX Message Queues.

The main communication flow is:

```text
User
 ↓
UI
 ↓
POSIX Message Queue
 ↓
Core
 ↓
CPU / Memory / Stack / Queue
 ↓
Result → UI
 ↓
Execution Message → Logger
```

The project successfully demonstrates the basic concepts of:

* Multi-process programming
* Inter-Process Communication
* POSIX Message Queues
* Process creation
* Process synchronization
* Modular programming
* Logging
* Integration of multiple system components

---

## 14. Conclusion

The Week 1 project provides a basic simulation of a computer system using multiple processes. Each component performs a specific task, while POSIX Message Queues allow the processes to communicate with each other.

The IPC integration connects the UI, Core, and Logger into a single working system. This provides the foundation for extending the simulator with additional functionality in future weeks.
