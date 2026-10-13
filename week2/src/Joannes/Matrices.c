#include <stdio.h>

#define MAX 100

int main() {
    int n, at[MAX], bt[MAX], ct[MAX];
    int wt[MAX], tat[MAX], rt[MAX];
    int time = 0, busy = 0, idle = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of processes!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);

        if (at[i] < 0 || bt[i] <= 0) {
            printf("Invalid input!\n");
            return 1;
        }
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    // FCFS scheduling
    for (int i = 0; i < n; i++) {
        if (time < at[i]) {
            idle += at[i] - time;
            time = at[i];
        }

        rt[i] = time - at[i];
        time += bt[i];
        ct[i] = time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        busy += bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i],
               wt[i], tat[i], rt[i]);
    }

    printf("\nAverage WT: %.2f", totalWT / n);
    printf("\nAverage TAT: %.2f", totalTAT / n);
    printf("\nCPU Busy Time: %d", busy);
    printf("\nCPU Idle Time: %d", idle);
    printf("\nCPU Utilization: %.2f%%\n",
           time > 0 ? (float)busy / time * 100 : 0);

    return 0;
}