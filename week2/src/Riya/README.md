# CPU Scheduling Algorithms

##  Overview

I'm implemented three CPU scheduling algorithms using the C programming language:

- Priority Non-Preemptive Scheduling
- Priority Preemptive Scheduling
- Round Robin Scheduling

The objective of this work is to implement and test different CPU scheduling techniques and evaluate their performance using scheduling metrics.

## Responsibilities and Contributions

### 1. Priority Non-Preemptive Scheduling

Implemented priority-based scheduling in which the CPU selects the highest-priority process from the available processes. Once a process begins execution, it continues until completion.

In this implementation, a smaller priority number represents a higher priority.

### 2. Priority Preemptive Scheduling

Implemented priority-based preemptive scheduling. When a higher-priority process arrives, it can interrupt the currently executing process. The interrupted process resumes later when selected by the scheduler.

### 3. Round Robin Scheduling

Implemented the Round Robin scheduling algorithm, which allocates CPU time to processes in turns using a configurable time quantum.

If a process does not complete within its allocated time, it returns to the ready queue for another execution turn.

##  Features Implemented

- Implementation of three CPU scheduling algorithms in C.
- Gantt chart generation to represent process execution order.
- Calculation of Completion Time (CT).
- Calculation of Waiting Time (WT).
- Calculation of Turnaround Time (TAT).
- Calculation of Response Time (RT).
- Calculation of average waiting time.
- Calculation of average turnaround time.
- Calculation of average response time.
- CPU utilization reporting where available in the program output.
- Configurable time quantum for Round Robin scheduling.


##  Performance Metrics

The following metrics are used to evaluate scheduling performance:

| Metric | Description |
|--------|-------------|
| Completion Time (CT) | Time at which a process finishes execution. |
| Waiting Time (WT) | Total time a process spends waiting for CPU execution. |
| Turnaround Time (TAT) | Total time between process arrival and completion. |
| Response Time (RT) | Time between process arrival and its first CPU allocation. |
| CPU Utilization | Percentage of the measured time during which the CPU is busy. |

##  Tools and Technologies

- Programming Language: C
- Compiler: GCC
- Development Environment: Visual Studio Code
- Version Control: Git and GitHub

##  Outcome

The implementation demonstrates how Priority Non-Preemptive, Priority Preemptive, and Round Robin scheduling manage CPU execution differently.

Gantt charts and performance metrics were used to inspect and compare the results obtained from the sample dataset.

Further testing with different process arrival times, burst times, priority values, time quantum values, and CPU idle periods can help validate the algorithms under additional conditions.

##  Conclusion

As Member 2, I contributed three CPU scheduling algorithms to the Process Scheduling Simulator project. This work provided practical experience in process scheduling, priority handling, preemption, ready-queue management, Gantt chart generation, and performance evaluation.