
#include <stdio.h>
#include "fcfs_sjf.h"

static void reset(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
        p[i].completion_time = p[i].first_start_time = -1;
        p[i].started = 0;
    }
}

static void add(Segment g[], int *n, int pid, int s, int e) {
    if (s >= e) return;
    if (*n && g[*n-1].pid == pid && g[*n-1].end_time == s) {
        g[*n-1].end_time = e;
        return;
    }
    if (*n >= MAX_SEGMENTS) {
        fprintf(stderr, "Gantt chart capacity exceeded.\n");
        return;
    }
    g[*n] = (Segment){pid, s, e};
    (*n)++;
}

void run_fcfs(Process p[], int n, Segment g[], int *count) {
    reset(p, n);
    *count = 0;
    int t = 0, done = 0;
    while (done < n) {
        int c = -1;
        for (int i = 0; i < n; i++)
            if (p[i].remaining_time > 0 && p[i].arrival_time <= t &&
                (c == -1 || p[i].arrival_time < p[c].arrival_time))
                c = i;
        if (c == -1) { add(g, count, -1, t, t+1); t++; continue; }
        if (!p[c].started) p[c].first_start_time = t, p[c].started = 1;
        int s = t;
        t += p[c].remaining_time;
        p[c].remaining_time = 0;
        p[c].completion_time = t;
        done++;
        add(g, count, p[c].pid, s, t);
    }
}

void run_sjf_non_preemptive(Process p[], int n, Segment g[], int *count) {
    reset(p, n);
    *count = 0;
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
        int s = t;
        t += p[c].remaining_time;
        p[c].remaining_time = 0;
        p[c].completion_time = t;
        done++;
        add(g, count, p[c].pid, s, t);
    }
}

void run_sjf_preemptive(Process p[], int n, Segment g[], int *count) {
    reset(p, n);
    *count = 0;
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
