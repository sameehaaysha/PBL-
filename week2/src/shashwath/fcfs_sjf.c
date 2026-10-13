
#include <stdio.h>
#include "fcfs_sjf.h"

static int valid_input(Process p[], int n, Segment g[], int *count) {
    if (!p || !g || !count || n <= 0 || n > MAX_PROCESSES) {
        fprintf(stderr, "Invalid scheduling input.\n");
        return 0;
    }
    for (int i = 0; i < n; i++)
        if (p[i].arrival_time < 0 || p[i].burst_time <= 0) {
            fprintf(stderr, "Invalid process arrival or burst time.\n");
            return 0;
        }
    *count = 0;
    return 1;
}

static void reset(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
        p[i].completion_time = p[i].first_start_time = -1;
        p[i].started = 0;
    }
}

static void add(Segment g[], int *count, int pid, int start, int end) {
    if (start >= end) return;
    if (*count > 0 && g[*count-1].pid == pid &&
        g[*count-1].end_time == start) {
        g[*count-1].end_time = end;
        return;
    }
    if (*count >= MAX_SEGMENTS) {
        fprintf(stderr, "Gantt chart capacity exceeded.\n");
        return;
    }
    g[*count] = (Segment){pid, start, end};
    (*count)++;
}

void run_fcfs(Process p[], int n, Segment g[], int *count) {
    if (!valid_input(p, n, g, count)) return;
    reset(p, n);
    int t = 0, done = 0;
    while (done < n) {
        int c = -1;
        for (int i = 0; i < n; i++)
            if (p[i].remaining_time > 0 && p[i].arrival_time <= t &&
                (c == -1 || p[i].arrival_time < p[c].arrival_time))
                c = i;
        if (c == -1) { add(g, count, -1, t, t+1); t++; continue; }
        if (!p[c].started) p[c].first_start_time = t, p[c].started = 1;
        int start = t;
        t += p[c].remaining_time;
        p[c].remaining_time = 0;
        p[c].completion_time = t;
        done++;
        add(g, count, p[c].pid, start, t);
    }
}

void run_sjf_non_preemptive(Process p[], int n, Segment g[], int *count) {
    if (!valid_input(p, n, g, count)) return;
    reset(p, n);
    int t = 0, done = 0;
    while (done < n) {
        int c = -1;
        for (int i = 0; i < n; i++)
            if (p[i].remaining_time > 0 && p[i].arrival_time <= t &&
                (c == -1 || p[i].burst_time < p[c].burst_time ||
                 (p[i].burst_time == p[c].burst_time &&
                  p[i].arrival_time < p[c].arrival_time)))
                c = i;
        if (c == -1) { add(g, count, -1, t, t+1); t++; continue; }
        p[c].first_start_time = t;
        p[c].started = 1;
        int start = t;
        t += p[c].remaining_time;
        p[c].remaining_time = 0;
        p[c].completion_time = t;
        done++;
        add(g, count, p[c].pid, start, t);
    }
}

void run_sjf_preemptive(Process p[], int n, Segment g[], int *count) {
    if (!valid_input(p, n, g, count)) return;
    reset(p, n);
    int t = 0, done = 0;
    while (done < n) {
        int c = -1;
        for (int i = 0; i < n; i++)
            if (p[i].remaining_time > 0 && p[i].arrival_time <= t &&
                (c == -1 || p[i].remaining_time < p[c].remaining_time ||
                 (p[i].remaining_time == p[c].remaining_time &&
                  p[i].arrival_time < p[c].arrival_time)))
                c = i;
        if (c == -1) { add(g, count, -1, t, t+1); t++; continue; }
        if (!p[c].started) p[c].first_start_time = t, p[c].started = 1;
        add(g, count, p[c].pid, t, t+1);
        if (--p[c].remaining_time == 0) p[c].completion_time = t+1, done++;
        t++;
    }
}
