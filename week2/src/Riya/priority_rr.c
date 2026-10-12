#include <stdio.h>
#include "priority_rr.h"

#define MAX 100

/* Display scheduling results */
static void display_results(Process p[], int n, int busy_time, int total_time)
{
    int i;
    float total_wt = 0;
    float total_tat = 0;
    float total_rt = 0;

    printf("\nPID\tCT\tWT\tTAT\tRT\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].completion_time,
               p[i].waiting_time,
               p[i].turnaround_time,
               p[i].response_time);

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);

    if (total_time > 0) {
        printf("CPU Utilization: %.2f%%\n",
               (float)busy_time / total_time * 100.0f);
    }
}

/* Validate the input processes */
static int valid_processes(Process p[], int n)
{
    int i;

    if (n <= 0 || n > MAX) {
        printf("Error: Number of processes must be between 1 and %d.\n", MAX);
        return 0;
    }

    for (i = 0; i < n; i++) {
        if (p[i].arrival_time < 0 || p[i].burst_time <= 0) {
            printf("Error: Arrival time must be non-negative and burst time positive.\n");
            return 0;
        }
    }

    return 1;
}

/* Priority Non-Preemptive */
void priority_non_preemptive(Process p[], int n)
{
    int done[MAX] = {0};
    int time = 0, completed = 0, busy_time = 0;
    int i, k;

    if (!valid_processes(p, n))
        return;

    for (i = 0; i < n; i++) {
        p[i].completion_time = 0;
        p[i].turnaround_time = 0;
        p[i].waiting_time = 0;
        p[i].response_time = -1;
    }

    printf("\n=== Priority Non-Preemptive ===\n");
    printf("Gantt Chart:\n");

    while (completed < n) {
        k = -1;

        for (i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival_time <= time) {
                if (k == -1 ||
                    p[i].priority < p[k].priority ||
                    (p[i].priority == p[k].priority &&
                     p[i].arrival_time < p[k].arrival_time)) {
                    k = i;
                }
            }
        }

        if (k == -1) {
            printf("| IDLE [%d-%d] ", time, time + 1);
            time++;
            continue;
        }

        printf("| P%d [%d-%d] ",
               p[k].pid, time, time + p[k].burst_time);

        p[k].response_time = time - p[k].arrival_time;

        time += p[k].burst_time;
        busy_time += p[k].burst_time;

        p[k].completion_time = time;
        p[k].turnaround_time = time - p[k].arrival_time;
        p[k].waiting_time =
            p[k].turnaround_time - p[k].burst_time;

        done[k] = 1;
        completed++;
    }

    printf("|\n");

    display_results(p, n, busy_time, time);
}

/* Priority Preemptive */
void priority_preemptive(Process p[], int n)
{
    int remaining[MAX];
    int time = 0, completed = 0, busy_time = 0;
    int i, k;
    int current = -2, segment_start = 0;

    if (!valid_processes(p, n))
        return;

    for (i = 0; i < n; i++) {
        remaining[i] = p[i].burst_time;
        p[i].completion_time = 0;
        p[i].turnaround_time = 0;
        p[i].waiting_time = 0;
        p[i].response_time = -1;
    }

    printf("\n=== Priority Preemptive ===\n");
    printf("Gantt Chart:\n");

    while (completed < n) {
        k = -1;

        for (i = 0; i < n; i++) {
            if (remaining[i] > 0 && p[i].arrival_time <= time) {
                if (k == -1 ||
                    p[i].priority < p[k].priority ||
                    (p[i].priority == p[k].priority &&
                     p[i].arrival_time < p[k].arrival_time)) {
                    k = i;
                }
            }
        }

        if (k != current) {
            if (current == -1)
                printf("| IDLE [%d-%d] ", segment_start, time);
            else if (current >= 0)
                printf("| P%d [%d-%d] ",
                       p[current].pid, segment_start, time);

            current = k;
            segment_start = time;
        }

        if (k == -1) {
            time++;
            continue;
        }

        if (p[k].response_time == -1)
            p[k].response_time = time - p[k].arrival_time;

        remaining[k]--;
        time++;
        busy_time++;

        if (remaining[k] == 0) {
            p[k].completion_time = time;
            p[k].turnaround_time = time - p[k].arrival_time;
            p[k].waiting_time =
                p[k].turnaround_time - p[k].burst_time;

            completed++;
        }
    }

    if (current == -1)
        printf("| IDLE [%d-%d] ", segment_start, time);
    else if (current >= 0)
        printf("| P%d [%d-%d] ",
               p[current].pid, segment_start, time);

    printf("|\n");

    display_results(p, n, busy_time, time);
}

/* Round Robin */
void round_robin(Process p[], int n, int quantum)
{
    int remaining[MAX];
    int queue[MAX + 1];
    int front = 0, rear = 0;
    int time = 0, completed = 0, busy_time = 0;
    int i, k, run;
    int segment_start = 0;
    int current = -2;

    if (!valid_processes(p, n))
        return;

    if (quantum <= 0) {
        printf("Error: Time quantum must be positive.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        remaining[i] = p[i].burst_time;
        p[i].completion_time = 0;
        p[i].turnaround_time = 0;
        p[i].waiting_time = 0;
        p[i].response_time = -1;
    }

    printf("\n=== Round Robin (Quantum = %d) ===\n", quantum);
    printf("Gantt Chart:\n");

    while (completed < n) {
        /* Add processes that have arrived and are not yet completed. */
        for (i = 0; i < n; i++) {
            if (remaining[i] > 0 &&
                p[i].arrival_time <= time) {

                int j;
                int already_queued = 0;
                int pos = front;

                while (pos != rear) {
                    if (queue[pos] == i) {
                        already_queued = 1;
                        break;
                    }
                    pos = (pos + 1) % (MAX + 1);
                }

                if (!already_queued &&
                    (current != i || remaining[i] == p[i].burst_time)) {
                    /* Enqueue only when this process is ready. */
                    if (current != i) {
                        queue[rear] = i;
                        rear = (rear + 1) % (MAX + 1);
                    }
                }
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        k = queue[front];
        front = (front + 1) % (MAX + 1);

        if (current >= 0) {
            printf("| P%d [%d-%d] ",
                   current + 1, segment_start, time);
        }

        current = k;
        segment_start = time;

        if (p[k].response_time == -1)
            p[k].response_time = time - p[k].arrival_time;

        run = remaining[k] < quantum ? remaining[k] : quantum;

        remaining[k] -= run;
        time += run;
        busy_time += run;

        if (remaining[k] == 0) {
            p[k].completion_time = time;
            p[k].turnaround_time =
                time - p[k].arrival_time;
            p[k].waiting_time =
                p[k].turnaround_time - p[k].burst_time;
            completed++;
        }
    }

    if (current >= 0) {
        printf("| P%d [%d-%d] ", current + 1, segment_start, time);
    }

    printf("|\n");
    display_results(p, n, busy_time, time);
}