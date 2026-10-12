# CPU Process Scheduling Simulator

## 1. Project Description
The CPU Process Scheduling Simulator is a C-based project that demonstrates how an operating system schedules processes for CPU execution. It implements six scheduling algorithms and calculates performance metrics to compare their efficiency.

## 2. Features
- Implements FCFS (First Come First Served).
- Implements SJF (Shortest Job First).
- Implements SRTF (Shortest Remaining Time First).
- Implements Non-preemptive Priority Scheduling.
- Implements Preemptive Priority Scheduling.
- Implements Round Robin Scheduling.
- Calculates Waiting Time (WT) for each process.
- Calculates Turnaround Time (TAT) for each process.
- Calculates Response Time (RT) for each process.
- Calculates Average Waiting Time and Average Turnaround Time.
- Calculates CPU Utilization and CPU Idle Time.
- Compares the performance of scheduling algorithms.

## 3. Technologies Used
- Programming Language: C
- Compiler: GCC
- Editor: Visual Studio Code
- Version Control: Git and GitHub

## 4. Input Parameters
The simulator uses the following process information:
- Process ID (PID)
- Arrival Time (AT)
- Burst Time (BT)
- Priority (for Priority Scheduling)
- Time Quantum (for Round Robin)

## 5. Performance Metrics
- Waiting Time (WT): Time a process spends waiting for CPU execution.
- Turnaround Time (TAT): Total time from process arrival to completion.
- Response Time (RT): Time from process arrival until its first CPU execution.
- Average Waiting Time: Average waiting time of all processes.
- Average Turnaround Time: Average turnaround time of all processes.
- CPU Utilization: Percentage of elapsed time during which the CPU is busy.
- CPU Idle Time: Total time during which the CPU has no process to execute.

## 6. Compilation and Execution

### Prerequisites
Install GCC and ensure it is available in the system PATH.

### Compilation
Open the terminal in Visual Studio Code and navigate to the directory containing the C source file.

Compile the program using:

```bash
gcc filename.c -o simulator