
#include <stdio.h>
#include <string.h>
#include "deadlock.h"

int bankers_algorithm(SystemState *s)
{
    int w[MAX_RESOURCES], done[MAX_PROCESSES] = {0}, n = 0;

    if (!s || s->process_count < 1 || s->process_count > MAX_PROCESSES ||
        s->resource_count < 1 || s->resource_count > MAX_RESOURCES)
        return 0;

    for (int j = 0; j < s->resource_count; j++)
        if ((w[j] = s->available[j]) < 0) return 0;

    for (int i = 0; i < s->process_count; i++)
        done[i] = s->processes[i].completed;

    while (n < s->process_count) {
        int found = 0;
        for (int i = 0; i < s->process_count; i++) {
            if (done[i]) continue;
            int j;
            for (j = 0; j < s->resource_count; j++)
                if (s->need[i][j] < 0 ||
                    s->need[i][j] > w[j]) break;
            if (j != s->resource_count) continue;

            for (j = 0; j < s->resource_count; j++)
                w[j] += s->allocation[i][j];
            done[i] = found = 1;
            s->safe_sequence[n++] = s->processes[i].pid;
            break;
        }
        if (!found) break;
    }
    s->safe_sequence_length = n;
    for (int i = 0; i < s->process_count; i++)
        if (!done[i]) return 0;
    return 1;
}

int detect_deadlock(SystemState *s)
{
    int w[MAX_RESOURCES], done[MAX_PROCESSES] = {0};

    s->deadlocked_count = 0;
    for (int j = 0; j < s->resource_count; j++)
        w[j] = s->available[j];

    for (int i = 0; i < s->process_count; i++) {
        int has = 0;
        for (int j = 0; j < s->resource_count; j++)
            if (s->allocation[i][j] > 0) has = 1;
        done[i] = s->processes[i].completed || !has;
    }

    for (int changed = 1; changed;) {
        changed = 0;
        for (int i = 0; i < s->process_count; i++) {
            if (done[i]) continue;
            int j;
            for (j = 0; j < s->resource_count; j++)
                if (s->request[i][j] > w[j]) break;
            if (j != s->resource_count) continue;

            for (j = 0; j < s->resource_count; j++)
                w[j] += s->allocation[i][j];
            done[i] = 1;
            changed = 1;
        }
    }

    for (int i = 0; i < s->process_count; i++) {
        s->processes[i].deadlocked = !done[i];
        if (!done[i]) s->deadlocked[s->deadlocked_count++] = i;
    }
    return s->deadlocked_count;
}

int request_resources(SystemState *s, int pid, int req[])
{
    if (!s || !req || pid < 0 || pid >= s->process_count ||
        s->processes[pid].completed) return 0;

    for (int j = 0; j < s->resource_count; j++)
        if (req[j] < 0 || req[j] > s->need[pid][j]) return 0;

    for (int j = 0; j < s->resource_count; j++)
        s->request[pid][j] = req[j];

    for (int j = 0; j < s->resource_count; j++)
        if (req[j] > s->available[j]) return 0;

    for (int j = 0; j < s->resource_count; j++) {
        s->available[j] -= req[j];
        s->allocation[pid][j] += req[j];
        s->need[pid][j] -= req[j];
        s->request[pid][j] = 0;
    }

    if (!bankers_algorithm(s)) {
        for (int j = 0; j < s->resource_count; j++) {
            s->available[j] += req[j];
            s->allocation[pid][j] -= req[j];
            s->need[pid][j] += req[j];
            s->request[pid][j] = req[j];
        }
        return 0;
    }

    for (int j = 0; j < s->resource_count; j++) {
        s->processes[pid].allocation[j] = s->allocation[pid][j];
        s->processes[pid].need[j] = s->need[pid][j];
    }
    return 1;
}

void recover_from_deadlock(SystemState *s)
{
    if (detect_deadlock(s) == 0) {
        puts("No deadlock detected.");
        return;
    }

    int p = s->deadlocked[0];
    printf("Terminating process %d to recover.\n", s->processes[p].pid);

    for (int j = 0; j < s->resource_count; j++) {
        s->available[j] += s->allocation[p][j];
        s->allocation[p][j] = s->processes[p].allocation[j] = 0;
        s->request[p][j] = 0;
        s->need[p][j] = s->processes[p].need[j] = 0;
    }
    s->processes[p].completed = 1;
    s->processes[p].deadlocked = 0;

    detect_deadlock(s);
}
