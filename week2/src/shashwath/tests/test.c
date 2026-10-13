
#include <stdio.h>
#include "../fcfs_sjf.h"

static void print_results(const char *name,
                          Process p[], int n,
                          Segment g[], int count)
{
    printf("\n=== %s ===\n", name);
    printf("Gantt chart:\n");

    for (int i = 0; i < count; i++) {
        if (g[i].pid == -1)
            printf("| IDLE %d-%d ",
                   g[i].start_time, g[i].end_time);
        else
            printf("| P%d %d-%d ",
                   g[i].pid, g[i].start_time, g[i].end_time);
    }
    printf("|\n\n");

    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    double total_wt = 0;
    double total_tat = 0;
    double total_busy = 0;
    int first_arrival = p[0].arrival_time;
    int last_completion = 0;

    for (int i = 0; i < n; i++) {
        int tat = p[i].completion_time - p[i].arrival_time;
        int wt = tat - p[i].burst_time;
        int rt = p[i].first_start_time - p[i].arrival_time;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time,
               p[i].burst_time, p[i].completion_time,
               tat, wt, rt);

        total_wt += wt;
        total_tat += tat;
        total_busy += p[i].burst_time;

        if (p[i].arrival_time < first_arrival)
            first_arrival = p[i].arrival_time;
        if (p[i].completion_time > last_completion)
            last_completion = p[i].completion_time;
    }

    printf("Average WT: %.2f\n", total_wt / n);
    printf("Average TAT: %.2f\n", total_tat / n);

    int elapsed = last_completion;
    printf("CPU Utilization: %.2f%%\n",
           elapsed > 0 ? 100.0 * total_busy / elapsed : 0.0);
}

int main(void)
{
   Process original[] = {
    {.pid=1, .arrival_time=0, .burst_time=8, .priority=1},
    {.pid=2, .arrival_time=2, .burst_time=2, .priority=2},
    {.pid=3, .arrival_time=3, .burst_time=1, .priority=3}
};
    const int n = sizeof(original) / sizeof(original[0]);
    Process p[MAX_PROCESSES];
    Segment g[MAX_SEGMENTS];
    int count;

    for (int algorithm = 0; algorithm < 3; algorithm++) {
        for (int i = 0; i < n; i++)
            p[i] = original[i];

        if (algorithm == 0) {
            run_fcfs(p, n, g, &count);
            print_results("FCFS", p, n, g, count);
        } else if (algorithm == 1) {
            run_sjf_non_preemptive(p, n, g, &count);
            print_results("SJF Non-preemptive", p, n, g, count);
        } else {
            run_sjf_preemptive(p, n, g, &count);
            print_results("SJF Preemptive", p, n, g, count);
        }
    }

    return 0;
}
