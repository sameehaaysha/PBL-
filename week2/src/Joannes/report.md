# Project Report: CPU Process Scheduling Simulator

## 1. Introduction
CPU scheduling is an important function of an operating system. It decides which process gets CPU time and in what order. This project implements six CPU scheduling algorithms using C and compares their performance.

## 2. Scheduling Algorithms

### 1. FCFS (First Come First Served)
Processes are executed in the order they arrive. It is simple to implement but may cause longer waiting times when a long process arrives first.

### 2. SJF (Shortest Job First)
The process with the shortest burst time is executed first. It can reduce average waiting time, but longer processes may wait for a long time.

### 3. SRTF (Shortest Remaining Time First)
This is the preemptive version of SJF. The CPU executes the process with the shortest remaining time. A running process can be interrupted when a shorter process arrives.

### 4. Non-preemptive Priority Scheduling
The CPU selects the process with the highest priority. Once execution starts, the process continues until completion. Low-priority processes may experience long waiting times.

### 5. Preemptive Priority Scheduling
The CPU can interrupt a running process if a higher-priority process arrives. It provides faster service to high-priority processes but may delay low-priority processes.

### 6. Round Robin (RR)
Each process receives CPU time for a fixed period called the time quantum. If the process is not completed, it returns to the ready queue. This algorithm is suitable for time-sharing systems.

## 3. Performance Metrics
The simulator calculates the following metrics:

- **Waiting Time (WT):** Time a process spends waiting for CPU execution.
- **Turnaround Time (TAT):** Total time from process arrival to completion.
- **Response Time (RT):** Time from process arrival until its first CPU execution.
- **Average Waiting Time:** Average waiting time of all processes.
- **Average Turnaround Time:** Average turnaround time of all processes.
- **CPU Utilization:** Percentage of elapsed time the CPU is busy.
- **CPU Idle Time:** Time when the CPU has no process to execute.

## 4. Observations About Performance

- **FCFS:** Simple and fair in arrival order, but a long process can delay shorter processes.
- **SJF:** Often provides a low average waiting time when burst times are known.
- **SRTF:** Can reduce waiting time further by allowing shorter jobs to run first.
- **Non-preemptive Priority:** Executes high-priority processes first but may delay low-priority processes.
- **Preemptive Priority:** Responds quickly to higher-priority processes but can cause starvation.
- **Round Robin:** Gives processes regular turns and is useful for interactive systems. Its performance depends on the time quantum.

## 5. Conclusion
This project demonstrates how different CPU scheduling algorithms manage process execution. Each algorithm has advantages and limitations. Their performance can be compared using waiting time, turnaround time, response time, CPU utilization, and CPU idle time.

The best algorithm depends on the system's requirements and the processes being executed.