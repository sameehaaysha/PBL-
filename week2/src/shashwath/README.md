FCFS and SJF Process Scheduling

1. Role and Responsibilities

Member 1 is responsible for implementing and testing the following CPU scheduling algorithms in C:

- First Come First Serve (FCFS)
- Shortest Job First (SJF) — Non-Preemptive
- Shortest Job First (SJF) — Preemptive

The objective is to implement the scheduling algorithms, handle process arrival times and CPU idle periods, generate Gantt chart data, and support the calculation of scheduling performance metrics.

2. Requirements from the Week 3 PDF

The Week 3 Process Scheduling assignment requires the team to develop a CPU scheduling simulator supporting six algorithms:

1. First Come First Serve (FCFS)
2. SJF Non-Preemptive
3. SJF Preemptive
4. Priority Non-Preemptive
5. Priority Preemptive
6. Round Robin (RR) with a configurable time quantum

The assignment also requires:

- Process inputs: PID, arrival time, burst time, and priority.
- Gantt chart representation of process execution.
- Calculation of waiting time (WT), turnaround time (TAT), and response time (RT).
- Average waiting time and average turnaround time.
- CPU utilization.
- Handling of process arrival times, CPU idle periods, and process completion.
- At least three test cases.
- Source code, testing, and documentation.

Member 1 is responsible for the FCFS and SJF algorithms. The remaining algorithms and overall integration are handled by the other team members.

3. Implemented Algorithms

3.1 First Come First Serve (FCFS)

FCFS schedules processes according to their arrival order.

Implementation features:

- Selects the earliest-arriving available process.
- Executes each selected process until completion.
- Handles CPU idle periods when no process is ready.
- Records execution intervals for Gantt chart generation.

3.2 SJF Non-Preemptive

Non-preemptive SJF selects the available process with the shortest burst time.

Implementation features:

- Selects the shortest available job.
- Executes the selected process until completion.
- Uses arrival time as a tie-breaker when burst times are equal.
- Records process start and completion times.

3.3 SJF Preemptive

Preemptive SJF, also known as Shortest Remaining Time First (SRTF), selects the available process with the shortest remaining execution time.

Implementation features:

- Re-evaluates process selection as time advances.
- Supports preemption when a process with a shorter remaining time becomes available.
- Records first execution and completion times.
- Generates time-based scheduling segments for the Gantt chart.

4. Project Structure

shashwath/
├── fcfs_sjf.c
├── fcfs_sjf.h
├── tests/
│   ├── test.c
│   └── test_results.md
└── README.md

The implementation uses the team's shared "common.h" header for the "Process" and "Segment" structures. The include path must match the repository's actual directory structure.

File Descriptions

File| Description
"fcfs_sjf.c"| Implements FCFS and both SJF algorithms.
"fcfs_sjf.h"| Declares the scheduling functions.
"tests/test.c"| Runs standalone scheduling tests.
"tests/test_results.md"| Documents test cases and expected results.
"README.md"| Documents Member 1's responsibilities and implementation.

5. Testing

The implementation is tested using multiple process configurations.

Test Case 1 — CPU Idle Periods

Objective:

- Verify CPU idle-period handling.
- Check process arrival-time handling.
- Validate waiting time, turnaround time, and CPU utilization.

Test Case 2 — Simultaneous Arrivals

Objective:

- Verify FCFS scheduling order.
- Verify shortest-job selection.
- Check behavior when multiple processes arrive simultaneously.

Test Case 3 — Preemption

Objective:

- Verify preemptive SJF process selection.
- Check execution segments and completion times.
- Validate response time, waiting time, and turnaround time.

Detailed test results are documented in "tests/test_results.md".

6. Compilation and Execution

Compile the implementation and test program from the "shashwath" directory:

gcc -Wall -Wextra -std=c11 fcfs_sjf.c tests/test.c -o test_member1

Run the test program:

./test_member1

The compilation command assumes the shared header is accessible through the include paths specified in the header files.

7. Expected Output

The test program displays scheduling information, including:

- Gantt chart execution segments.
- Process completion times.
- Waiting times.
- Turnaround times.
- Response times.
- Average scheduling metrics.
- CPU utilization.

The results are used to verify the algorithms and support integration with the complete scheduling simulator.

8. Team Integration

The scheduling algorithms are implemented as separate functions to support integration into the team's simulator.

The integrated project must ensure that:

- All modules use compatible shared process structures.
- Function declarations match their implementations.
- Gantt chart data and scheduling metrics are compatible with the user interface.
- The complete project compiles and passes integration tests.

9. Contribution Summary

Member 1's contribution focuses on implementing and testing FCFS, SJF Non-Preemptive, and SJF Preemptive scheduling algorithms in C.

The implementation covers process selection, arrival-time handling, CPU idle periods, completion-time tracking, Gantt chart generation, and standalone testing.

These algorithms form the FCFS/SJF component of the team's Process Scheduling Simulator.