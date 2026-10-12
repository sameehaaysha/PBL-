
# MEMBER 1 — FCFS AND SJF TEST RESULTS

## Test Case 1: CPU Idle Periods
Processes:
P1: AT=3, BT=2
P2: AT=8, BT=1

Gantt chart:
IDLE (0-3) -> P1 (3-5) -> IDLE (5-8) -> P2 (8-9)

Average WT: 0.00
Average TAT: 1.50
CPU Utilization: 33.33%

## Test Case 2: Simultaneous Arrivals
Processes:
P1: AT=0, BT=4
P2: AT=0, BT=2
P3: AT=0, BT=1

FCFS:
Average WT: 3.33
Average TAT: 5.67

SJF Non-preemptive:
Average WT: 1.33
Average TAT: 3.67

SJF Preemptive:
Average WT: 1.33
Average TAT: 3.67

## Test Case 3: Preemption
Processes:
P1: AT=0, BT=8
P2: AT=2, BT=2
P3: AT=3, BT=1

SJF Preemptive Gantt chart:
P1 (0-2) -> P2 (2-4) -> P3 (4-5) -> P1 (5-11)

Average WT: 1.33
Average TAT: 5.00
CPU Utilization: 100.00%
