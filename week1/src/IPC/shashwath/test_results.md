# WEEK 1 IPC IMPLEMENTATION — TEST RESULTS

## 1. OBJECTIVE

To test the compilation and functionality of the Message Queue module, Signals module, and Logger implementation using GCC in a WSL environment.

## 2. TEST ENVIRONMENT

- Operating environment: Ubuntu on WSL
- Programming language: C
- Compiler: GCC
- Message Queue mechanism: POSIX Message Queues
- Signal mechanism: SIGUSR1
- Logging mechanism: POSIX Message Queue and file-based logging

## 3. TEST CASES AND RESULTS

### TEST CASE 1: MESSAGE QUEUE COMPILATION

**Objective:** Verify that the Message Queue module compiles successfully.

**Result:** PASS

**Evidence:** The file `/tmp/message_queue.o` was generated without compiler errors or warnings.

### TEST CASE 2: SIGNALS COMPILATION

**Objective:** Verify that the Signals module compiles successfully.

**Result:** PASS

**Evidence:** The file `/tmp/signals.o` was generated without compiler errors or warnings.

### TEST CASE 3: LOGGER COMPILATION

**Objective:** Verify that the Logger executable can be generated.

**Result:** PASS

**Evidence:** The executable `/tmp/logger` was created successfully.

### TEST CASE 4: MESSAGE QUEUE SEND AND RECEIVE

**Objective:** Verify that a message can be transmitted and received through a POSIX message queue.

**Test message:** `HELLO_FROM_TEST`

**Actual result:** The sent and received messages matched exactly.

**Result:** PASS

### TEST CASE 5: SIGNAL HANDLING

**Objective:** Verify that the signal handler can detect SIGUSR1.

**Actual result:** The test program successfully registered its signal handler, sent SIGUSR1 to itself, and detected the received signal.

**Result:** PASS

**Limitation:** This test verifies signal handling within the same process. Inter-process signal delivery remains to be tested.

### TEST CASE 6: LOGGER EVENT PROCESSING

**Objective:** Verify that the Logger receives and processes informational, error, and shutdown events.

**Actual result:** The Logger processed all three events and terminated after receiving the expected shutdown message.

**Result:** PASS

### TEST CASE 7: EXECUTION LOG GENERATION

**Objective:** Verify that ordinary events are written to the execution log with timestamps and severity labels.

**Actual result:** The test event was successfully recorded in `logs/execution.log`.

**Result:** PASS

### TEST CASE 8: ERROR LOG GENERATION

**Objective:** Verify that error events are recorded separately from ordinary events.

**Actual result:** The simulated error was successfully recorded in `logs/error.log`.

**Result:** PASS

### TEST CASE 9: LOGGER SHUTDOWN

**Objective:** Verify that the Logger stops when it receives the designated shutdown message.

**Actual result:** The terminal displayed `Logger stopped.` and the process exited successfully.

**Result:** PASS

## 4. TEST SUMMARY

The Message Queue, Signals, and Logger modules compiled successfully.

The Message Queue send-and-receive test passed, and the Signals test successfully detected SIGUSR1 within the same process.

The Logger successfully processed test events, wrote informational and error messages to their respective log files, and terminated cleanly.

Separate-process IPC communication and integration with the common UI require additional testing.

## 5. CONCLUSION

The initial compilation and runtime tests demonstrate that the individual Message Queue, Signals, and Logger components perform their tested operations successfully.

Further testing is required to verify inter-process communication, integration between the IPC modules and Logger, and operation through the common user interface.