#include <stdio.h>
#include "process.h"

void input_processes(Process p[], int n)
{
for (int i = 0; i < n; i++)
{
printf("\nEnter details for Process %d\n", i + 1);


    printf("Enter Process ID: ");
    if (scanf("%d", &p[i].pid) != 1)
    {
        printf("Invalid Process ID!\n");
        return;
    }

    printf("Enter Arrival Time: ");
    if (scanf("%d", &p[i].arrival_time) != 1 ||
        p[i].arrival_time < 0)
    {
        printf("Invalid Arrival Time!\n");
        return;
    }

    printf("Enter Burst Time: ");
    if (scanf("%d", &p[i].burst_time) != 1 ||
        p[i].burst_time <= 0)
    {
        printf("Burst time must be greater than zero!\n");
        return;
    }

    printf("Enter Priority: ");
    if (scanf("%d", &p[i].priority) != 1)
    {
        printf("Invalid Priority!\n");
        return;
    }

    p[i].remaining_time = p[i].burst_time;
    p[i].completion_time = 0;
    p[i].first_start_time = -1;
    p[i].started = 0;
}

printf("\nAll process details entered successfully!\n");


}

void display_processes(const Process p[], int n)
{
printf("\n============================================\n");
printf("           PROCESS INFORMATION\n");
printf("============================================\n");


printf("PID\tArrival\tBurst\tPriority\n");

for (int i = 0; i < n; i++)
{
    printf("%d\t%d\t%d\t%d\n",
           p[i].pid,
           p[i].arrival_time,
           p[i].burst_time,
           p[i].priority);
}

printf("============================================\n");


}
