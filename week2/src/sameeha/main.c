

#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "../shashwath/fcfs_sjf.h"
#include "../Riya/priority_rr.h"

#define MAX 100

static void display_gantt_chart(const Segment gantt[], int count)
{
    int i;

    printf("\nGantt Chart:\n");

    for (i = 0; i < count; i++) {
        if (gantt[i].pid == -1) {
            printf("| Idle ");
        } else {
            printf("| P%d ", gantt[i].pid);
        }
    }

    printf("|\n");

    if (count > 0) {
        printf("%d", gantt[0].start_time);

        for (i = 0; i < count; i++) {
            printf("     %d", gantt[i].end_time);
        }

        printf("\n");
    }
}

int main(void)
{
    Process processes[MAX];
    Segment gantt[MAX_SEGMENTS];

    int n;
    int choice;
    int segment_count;

    printf("====================================\n");
    printf("   PROCESS SCHEDULING SIMULATOR\n");
    printf("====================================\n");

    printf("Enter number of processes (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of processes.\n");
        return EXIT_FAILURE;
    }

    input_processes(processes, n);

    do {
        printf("\n========== MENU ==========\n");
        printf("1. FCFS Scheduling\n");
        printf("2. SJF Non-Preemptive\n");
        printf("3. SJF Preemptive (SRTF)\n");
        printf("4. Priority Non-Preemptive\n");
        printf("5. Priority Preemptive\n");
        printf("6. Round Robin\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }

        switch (choice) {
            case 1:
                segment_count = 0;
                run_fcfs(processes, n, gantt, &segment_count);
                display_gantt_chart(gantt, segment_count);
                break;

            case 2:
                segment_count = 0;
                run_sjf_non_preemptive(
                    processes, n, gantt, &segment_count);
                display_gantt_chart(gantt, segment_count);
                break;

            case 3:
                segment_count = 0;
                run_sjf_preemptive(
                    processes, n, gantt, &segment_count);
                display_gantt_chart(gantt, segment_count);
                break;

            case 4:
                priority_non_preemptive(processes, n);
                break;

            case 5:
                priority_preemptive(processes, n);
                break;

            case 6: {
                int quantum;

                printf("Enter time quantum: ");

                if (scanf("%d", &quantum) != 1 || quantum <= 0) {
                    printf("Invalid time quantum.\n");
                    return EXIT_FAILURE;
                }

                round_robin(processes, n, quantum);
                break;
            }

            case 0:
                printf("Exiting simulator.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    return EXIT_SUCCESS;
}