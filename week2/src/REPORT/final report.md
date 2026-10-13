# CPU Scheduling Simulator – Week 3 Project Report

## 1. Project Information

* **Project Title:** Process Scheduling Simulator
* **Domain:** Operating Systems
* **Programming Language:** C
* **Project Type:** Problem-Based Learning (PBL)
* **Week:** 3

## 2. Abstract

The CPU Scheduling Simulator is a C-based project that demonstrates how an operating system schedules processes for CPU execution. It implements different scheduling algorithms and calculates performance metrics to help compare their results.

## 3. Objectives

* To understand CPU scheduling algorithms.
* To implement scheduling techniques using C.
* To display process execution using Gantt charts.
* To calculate waiting time, turnaround time, and response time.
* To compare the performance of different algorithms.

## 4. Algorithms Implemented

The project includes the following CPU scheduling algorithms:

* **FCFS (First-Come-First-Served):** Executes processes in arrival order.
* **SJF (Shortest Job First):** Selects the process with the shortest burst time.
* **Priority Scheduling:** Executes processes according to their priority.
* **Round Robin:** Gives each process a fixed time slice called a time quantum.

The project supports preemptive and non-preemptive scheduling where applicable.

## 5. Modules and Team Contributions

| Team Member | Responsibilities                              |
| ----------- | --------------------------------------------- |
| Sameeha     | Main program, process management, and menu    |
| Shashwath   | FCFS, SJF, and testing                        |
| Riya        | Priority Scheduling, Round Robin, and testing |
| Joannes     | Performance metrics and comparison utilities  |

## 6. Input and Output

**Inputs:**

* Number of processes
* Process ID
* Arrival time
* Burst time
* Priority
* Time quantum for Round Robin

**Outputs:**

* Gantt chart showing process execution
* Completion time
* Waiting time
* Turnaround time
* Response time
* Average waiting time and turnaround time
* CPU utilization

## 7. Performance Metrics

The simulator uses the following formulas:

* **Turnaround Time:** Completion Time − Arrival Time
* **Waiting Time:** Turnaround Time − Burst Time
* **Response Time:** First Start Time − Arrival Time
* **CPU Utilization:** (Total Busy CPU Time / Total Elapsed Time) × 100

## 8. Testing

The simulator is tested using different process arrival times, burst times, priorities, and time quantum values. These test cases help verify scheduling order, process execution, and performance calculations.

## 9. Conclusion

The CPU Scheduling Simulator provides a practical understanding of CPU scheduling algorithms using C. It helps compare different scheduling methods and understand how they affect process execution and CPU performance.

**Submitted as part of the Week 3 Problem-Based Learning (PBL) project.**