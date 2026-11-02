# WEEK 1 — INTER-PROCESS COMMUNICATION (IPC)

## 1. PROJECT OVERVIEW

This project implements and tests Inter-Process Communication (IPC) mechanisms in C. IPC allows separate processes to exchange information and coordinate their activities.

The individual contribution focuses on three components:

- POSIX Message Queues
- Signal Handling
- Logger Integration

These components demonstrate message-based communication, process signalling, and event recording.

## 2. INDIVIDUAL CONTRIBUTION

**Role:** IPC Module Implementation and Testing

### A. POSIX MESSAGE QUEUES

Implemented the Message Queue module to support sending and receiving structured messages between processes.

**Files:**
- `message_queue.c`
- `message_queue.h`

**Responsibilities:**
- Open named message queues.
- Send structured messages through a queue.
- Receive messages from a queue.
- Close queue descriptors after use.
- Handle errors during queue operations.
- Integrate queue operations with the Logger.

### B. SIGNAL HANDLING

Implemented a Signals module using POSIX signals to support communication between processes through operating-system signal delivery.

**Files:**
- `signals.c`
- `signals.h`

**Responsibilities:**
- Register handlers for `SIGUSR1` and `SIGUSR2`.
- Send signals to another process using `kill()`.
- Track pending signals using `volatile sig_atomic_t`.
- Retrieve and clear pending signal information.
- Record signal-related events through the Logger where appropriate.

The signal handlers use a minimal design: they update a signal-safe flag, while logging is performed outside the handler.

### C. LOGGER INTEGRATION

Worked with the Logger mechanism to record events generated during IPC operations.

**Files:**
- `logger.c`
- `logger.h`

**Responsibilities:**
- Transmit logging events through a POSIX Message Queue.
- Record execution-related events in `logs/execution.log`.
- Record error events in `logs/error.log`.
- Support the designated Logger shutdown message.

The Logger helps provide evidence of program execution and makes debugging easier.

## 3. PROJECT FILE STRUCTURE

```text
week1/
└── src/
    ├── IPC/
    │   ├── common.h
    │   ├── shashwath/
    │   │   ├── README.md
    │   │   ├── message_queue.c
    │   │   ├── message_queue.h
    │   │   ├── signals.c
    │   │   ├── signals.h
    │   │   └── test_results.md
    │   └── ipc.c
    ├── core/
    │   └── core.c
    ├── logger.c
    ├── logger.h
    └── ui.c
```

*Note: This structure describes the relevant project files. Other project directories and modules may also exist in the repository.*

## 4. TECHNOLOGIES USED

| Technology | Purpose |
|---|---|
| C | Implementation language |
| GCC | Compilation |
| POSIX Message Queues | Structured message exchange |
| POSIX Signals | Process signalling |
| `sigaction()` | Signal handler registration |
| `kill()` | Signal delivery |
| File I/O | Recording execution and error events |
| WSL | Development and testing environment |
| Git and GitHub | Version control and collaboration |

## 5. HOW THE COMPONENTS WORK

### MESSAGE QUEUE WORKFLOW

1. A process opens a named message queue.
2. The sending process prepares a structured message.
3. The message is transmitted using the queue.
4. The receiving process retrieves the message.
5. The queue descriptor is closed when no longer required.

### SIGNAL WORKFLOW

1. The receiving process installs its signal handler.
2. Another process sends a supported signal to the receiver.
3. The handler records the pending signal using a signal-safe flag.
4. The application retrieves the pending signal during normal execution.
5. The application can then process the signal and record relevant events.

### LOGGER WORKFLOW

1. An IPC operation generates an event.
2. The event is sent through the logging message queue.
3. The Logger receives and interprets the message.
4. Execution events are written to `logs/execution.log`.
5. Error events are written to `logs/error.log`.
6. The Logger terminates when it receives the designated shutdown message.

## 6. COMPILATION AND TESTING

Run the following commands from the `week1/src` directory in the WSL environment.

### COMPILE THE MESSAGE QUEUE MODULE

```bash
gcc -Wall -Wextra -std=c11 -c IPC/shashwath/message_queue.c -o /tmp/message_queue.o
```

### COMPILE THE SIGNALS MODULE

```bash
gcc -Wall -Wextra -std=c11 -c IPC/shashwath/signals.c -o /tmp/signals.o
```

### COMPILE THE LOGGER

```bash
gcc -Wall -Wextra -std=c11 logger.c -o logger -lrt
```

### RUN THE INTEGRATION TEST

The integration test source must be available at `/tmp/test_real_ipc.c`, and the Logger should be running separately.

Compile the test program:

```bash
gcc -Wall -Wextra -std=c11 /tmp/test_real_ipc.c IPC/shashwath/message_queue.c IPC/shashwath/signals.c -o /tmp/test_real_ipc -lrt
```

Start the Logger in one terminal:

```bash
./logger
```

Run the test program in another terminal:

```bash
/tmp/test_real_ipc
```

The test source at `/tmp/test_real_ipc.c` was used for the recorded development test. It is a temporary file, so it must be recreated or saved in the repository before another developer can reproduce the test directly from a fresh checkout.

## 7. TEST RESULTS

The recorded development tests reported successful results for:

| Test | Result |
|---|---|
| Message Queue compilation | PASS |
| Signals module compilation | PASS |
| Logger compilation | PASS |
| Message transmission | PASS |
| Message reception | PASS |
| Signal handler installation | PASS |
| Signal delivery between processes | PASS |
| Logger event processing | PASS |
| Execution log generation | PASS |
| Error log generation | PASS |
| Logger shutdown | PASS |
| Combined IPC integration test | PASS |

The combined integration test reported:

```text
MESSAGE QUEUE SEND: PASS
MESSAGE QUEUE RECEIVE: PASS

SIGNAL HANDLER INSTALLATION: PASS
SIGNAL SEND: PASS
SIGNAL RECEIVE: PASS

LOGGER SHUTDOWN REQUEST: PASS

OVERALL RESULT: PASS
```

Detailed test cases, evidence, limitations, and conclusions are documented in `test_results.md`.

These results apply to the recorded module and integration tests. They do not establish that the complete UI/Core application has been tested end to end.

## 8. LOG FILES

The Logger uses the following output files:

| File | Purpose |
|---|---|
| `logs/execution.log` | Records ordinary execution and informational events |
| `logs/error.log` | Records error events |

The logs are generated at runtime. They do not need to be committed to GitHub unless the project requirements explicitly request sample log output.

## 9. LIMITATIONS AND FUTURE WORK

The following activities remain relevant to complete system verification:

- Integrate the individual IPC modules with the complete UI and Core workflow.
- Verify end-to-end command transmission and response handling.
- Test queue and signal failure scenarios.
- Test repeated execution and shutdown cycles.
- Store the integration test source in the repository to make testing reproducible.
- Document additional test cases and their actual outputs.

The UI/Core integration should be coordinated with the team members responsible for those components.

## 10. CONCLUSION

The individual contribution implements POSIX Message Queue operations, POSIX signal handling, and Logger integration in C.

The recorded tests verified message transmission and reception, signal delivery between separate processes, logging behaviour, and Logger shutdown. The combined IPC integration test reported an overall passing result.

This work provides a foundation for communication and event recording within the larger application. Full application integration requires separate end-to-end verification.

## 11. VERSION CONTROL

The implementation and test documentation were committed and pushed to the project's GitHub repository.

**Commit message:** `Implement message queue, signals, and IPC logger`

**Development status:** Individual IPC implementation and recorded integration tests completed; full application integration requires separate verification.

