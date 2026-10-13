#include <stdio.h>
#include "priority_rr.h"

int main(void)
{
    int choice;
    int quantum = 2;

    Process p[3] = {
        {1, 0, 5, 2, 0, 0, 0, -1},
        {2, 1, 3, 1, 0, 0, 0, -1},
        {3, 2, 4, 3, 0, 0, 0, -1}
    };

    printf("\n===== SCHEDULING ALGORITHM TEST =====\n");
    printf("1. Priority Non-Preemptive\n");
    printf("2. Priority Preemptive\n");
    printf("3. Round Robin\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    switch (choice) {
        case 1:
            priority_non_preemptive(p, 3);
            break;

        case 2:
            priority_preemptive(p, 3);
            break;

        case 3:
            round_robin(p, 3, quantum);
            break;

        default:
            printf("Invalid choice.\n");
            return 1;
    }

    return 0;
}

