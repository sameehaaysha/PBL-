# WEEK 1 IPC IMPLEMENTATION — TEST RESULTS

## 1. OBJECTIVE

The objective of this testing phase is to verify the compilation and functionality of the following Inter-Process Communication (IPC) components implemented in C:

- POSIX Message Queues
- Signal Handling
- Logger and Event Recording

The tests evaluate whether messages can be transmitted and received, signals can be delivered and handled, and logging events can be recorded correctly.

## 2. TEST ENVIRONMENT

| Parameter | Details |
|---|---|
| Programming Language | C |
| Compiler | GCC |
| Development Environment | Ubuntu on WSL |
| Message Queue Mechanism | POSIX Message Queues |
| Signal Mechanism | POSIX Signals (`SIGUSR1`, `SIGUSR2`) |
| Logging Mechanism | POSIX Message Queue and file-based logging |
| Compiler Flags | `-Wall -Wextra -std=c11` |
| Additional Linker Flag | `-lrt` where required |

## 3. TEST CASES AND RESULTS

### TEST CASE 1: MESSAGE QUEUE MODULE COMPILATION

**Objective:** Verify that the Message Queue module compiles without errors or warnings.

**Command:**

```bash
gcc -Wall -Wextra -std=c11 -c IPC/shashwath/message_queue.c -o /tmp/message_queue.o
```

**Expected Result:** The source file should compile successfully.

**Actual Result:** Compilation completed successfully, and the object file was generated.

**Status: PASS**

### TEST CASE 2: SIGNALS MODULE COMPILATION

**Objective:** Verify that the Signals module compiles successfully.

**Command:**

```bash
gcc -Wall -Wextra -std=c11 -c IPC/shashwath/signals.c -o /tmp/signals.o
```

**Expected Result:** The source file should compile without errors or warnings.

**Actual Result:** Compilation completed successfully, and the object file was generated.

**Status: PASS**

### TEST CASE 3: LOGGER COMPILATION

**Objective:** Verify that the Logger program can be compiled into an executable.

**Command:**

```bash
gcc -Wall -Wextra -std=c11 logger.c -o logger -lrt
```

**Expected Result:** The compiler should generate the Logger executable successfully.

**Actual Result:** The Logger executable was generated and used in subsequent runtime tests.

**Status: PASS**

### TEST CASE 4: MESSAGE QUEUE SEND OPERATION

**Objective:** Verify that a message can be sent through a POSIX Message Queue.

**Procedure:**
1. Initialize the message queue.
2. Open the queue for sending.
3. Send a test message.
4. Check the operation result.

**Expected Result:** The message should be transmitted successfully.

**Actual Result:** The integration test reported successful message transmission.

**Status: PASS**

### TEST CASE 5: MESSAGE QUEUE RECEIVE OPERATION

**Objective:** Verify that a message transmitted through the queue can be received successfully.

**Procedure:**
1. Open the queue for receiving.
2. Receive the transmitted message.
3. Verify the receive operation.

**Expected Result:** The receiver should obtain the transmitted message successfully.

**Actual Result:** The integration test reported successful message reception.

**Status: PASS**

### TEST CASE 6: SIGNAL HANDLER INSTALLATION

**Objective:** Verify that the program can install a signal handler.

**Procedure:**
1. Configure the signal handler using `sigaction()`.
2. Register the handler for the required signal.
3. Verify the handler installation result.

**Expected Result:** The signal handler should be installed successfully.

**Actual Result:** The integration test reported successful signal handler installation.

**Status: PASS**

### TEST CASE 7: INTER-PROCESS SIGNAL TRANSMISSION

**Objective:** Verify that one process can send a signal to another process.

**Procedure:**
1. Start a receiver process.
2. Configure the receiver to handle `SIGUSR1`.
3. Send `SIGUSR1` from a separate sender process using `kill()`.
4. Verify that the receiver detects the signal.

**Expected Result:** The receiving process should detect the signal sent by the separate process.

**Actual Result:** The sender reported successful signal transmission, and the receiver reported receiving `SIGUSR1`.

**Observed Output:**

```text
Sent SIGUSR1 to process 8746
RESULT: PASS
Received SIGUSR1 from another process.
RESULT: PASS
```

The process ID shown above is from the recorded test run.

**Status: PASS**

### TEST CASE 8: LOGGER EVENT PROCESSING

**Objective:** Verify that the Logger receives and processes events delivered through the logging message queue.

**Procedure:**
1. Start the Logger process.
2. Send test events through the logging queue.
3. Verify that the Logger processes the events.

**Expected Result:** The Logger should process the submitted events.

**Actual Result:** The recorded integration test showed that the Logger processed Message Queue and signal-related events.

**Status: PASS**

### TEST CASE 9: EXECUTION LOG GENERATION

**Objective:** Verify that ordinary execution events are written to the execution log.

**Expected Result:** Informational and execution-related events should be recorded in `logs/execution.log`.

**Actual Result:** The generated execution log contained entries for tested Message Queue operations, signal-related operations, and Logger activity.

**Status: PASS**

### TEST CASE 10: ERROR LOG GENERATION

**Objective:** Verify that error events are recorded separately from ordinary execution events.

**Expected Result:** Error events should be written to `logs/error.log`.

**Actual Result:** In the dedicated Logger test, the simulated error event was recorded in the error log.

**Status: PASS**

### TEST CASE 11: LOGGER SHUTDOWN

**Objective:** Verify that the Logger terminates after receiving the designated shutdown message.

**Procedure:**
1. Start the Logger process.
2. Send the expected shutdown event.
3. Verify that the Logger exits.

**Expected Result:** The Logger should recognize the shutdown event and terminate cleanly.

**Actual Result:** The dedicated Logger test and the combined integration test reported successful shutdown handling.

**Status: PASS**

## 4. COMBINED INTEGRATION TEST

A combined test program was compiled using the Message Queue and Signals modules.

**Compilation command:**

```bash
gcc -Wall -Wextra -std=c11 /tmp/test_real_ipc.c IPC/shashwath/message_queue.c IPC/shashwath/signals.c -o /tmp/test_real_ipc -lrt
```

The Logger was started separately before executing the integration test.

**Recorded Test Output:**

```text
=== MESSAGE QUEUE INTEGRATION TEST ===
MESSAGE QUEUE SEND: PASS
MESSAGE QUEUE RECEIVE: PASS

=== SIGNALS INTEGRATION TEST ===
SIGNAL HANDLER INSTALLATION: PASS
SIGNAL SEND: PASS
SIGNAL RECEIVE: PASS

=== LOGGER SHUTDOWN REQUEST ===
LOGGER SHUTDOWN REQUEST: PASS

OVERALL RESULT: PASS
```

**Interpretation:**

- Message Queue send and receive operations completed successfully.
- Signal handler installation succeeded.
- Signal sending and receiving tests passed.
- The Logger processed the shutdown request successfully.
- The integration test reported an overall passing result.

**Overall Integration Test Status: PASS**

## 5. TEST SUMMARY

| Test ID | Component | Test Description | Result |
|---|---|---|---|
| TC-01 | Message Queue | Compilation | PASS |
| TC-02 | Signals | Compilation | PASS |
| TC-03 | Logger | Compilation | PASS |
| TC-04 | Message Queue | Message transmission | PASS |
| TC-05 | Message Queue | Message reception | PASS |
| TC-06 | Signals | Handler installation | PASS |
| TC-07 | Signals | Inter-process signal delivery | PASS |
| TC-08 | Logger | Event processing | PASS |
| TC-09 | Logger | Execution log generation | PASS |
| TC-10 | Logger | Error log generation | PASS |
| TC-11 | Logger | Shutdown handling | PASS |
| TC-12 | Integration | Combined Message Queue, Signals, and Logger testing | PASS |

**Total listed test cases: 12**

**Recorded result: 12 PASS**

*Note: The total counts the individual checks listed above, not 12 independently executed test programs. The results reflect the recorded compilation and runtime tests.*

## 6. LIMITATIONS AND PENDING VERIFICATION

Although the individual modules and recorded integration tests passed, the following items require separate verification:

1. **Full application integration:** The common UI and Core components must be tested together with the IPC modules.
2. **End-to-end application behaviour:** Commands entered through the UI should be checked to ensure that they reach the Core and produce the expected responses.
3. **Error-handling coverage:** Additional tests should verify behaviour when queues cannot be opened, messages cannot be transmitted, or a process terminates unexpectedly.
4. **Repeated execution:** Additional runs can verify behaviour across multiple consecutive executions and shutdown cycles.

The combined integration test does not, by itself, establish that the entire application is fully integrated.

## 7. CONCLUSION

The recorded tests demonstrate successful compilation of the Message Queue, Signals, and Logger modules. Runtime testing verified Message Queue transmission and reception, signal handling between separate processes, logging operations, and Logger shutdown behaviour.

The combined integration test reported an overall passing result. The execution and error logs also provided evidence that tested events were recorded through the logging mechanism.

The next stage is to verify these components within the complete application, including the common UI and Core workflow.

**Final Status: INDIVIDUAL MODULE TESTS AND RECORDED IPC INTEGRATION TESTS PASSED. FULL APPLICATION INTEGRATION REQUIRES SEPARATE VERIFICATION.**
