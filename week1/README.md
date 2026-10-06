# Multi-Process Simulator with POSIX IPC

A C-based multi-process simulator that demonstrates basic system operations (CPU, memory, stack, and queue) and Inter-Process Communication (IPC) using POSIX Message Queues.

**Platform:** Linux (Ubuntu) | **Language:** C | **Compiler:** GCC

## Overview

The simulator is split into three processes that communicate only through message queues:

- **UI** accepts commands from the user.
- **Core** executes the commands and returns results.
- **Logger** records execution and error events.

## How It Works

1. The user types a command in the UI.
2. The UI sends it to the Core through `/UI_TO_CORE`.
3. The Core executes it and sends the result back through `/CORE_TO_UI`.
4. The Core also sends a log entry to the Logger through `/CORE_TO_LOG`.
5. This repeats until the user enters `EXIT`.

## Features

- **CPU:** LOAD, ADD, SUB, MUL, DIV
- **Memory:** STORE, READ
- **Stack:** PUSH, POP, PEEK
- **Queue:** ENQUEUE, DEQUEUE, QPEEK
- Multi-process design using `fork()` and `execl()`
- Message-based IPC using POSIX Message Queues
- Centralized execution and error logging

## Project Structure

```text
week1/
├── src/
│   ├── core/
│   │   ├── core.c        # Command handling and dispatch
│   │   ├── cpu.c         # CPU operations
│   │   ├── memory.c      # Memory operations
│   │   ├── stack.c       # Stack operations
│   │   ├── queue.c       # Queue operations
│   │   └── simulator     # Compiled executable
│   ├── IPC/
│   │   ├── common.h      # Shared definitions
│   │   └── ipc.c         # Message queue setup and process integration
│   ├── logger.c          # Logging process
│   └── ui.c              # User interface process
└── README.md
```

## Technologies

C, GCC, Linux / Ubuntu, POSIX Message Queues

## Team

- **Sameeha** (Team Lead): IPC Integration
- **Riya Hency DSA**: Core
- **Shashwath Shetty**: Logger
- **Joannes**: UI

## Result

A working multi-process simulator that integrates Core, UI, Logger, and IPC through POSIX Message Queues.
