#ifndef COMMON_H
#define COMMON_H

#define MAX_PROCESSES 100
#define MAX_SEGMENTS 10000

typedef struct {
int pid;
int arrival_time;
int burst_time;
int priority;
int remaining_time;
int completion_time;
int first_start_time;
int started;
} Process;

typedef struct {
int pid;
int start_time;
int end_time;
} Segment;

#endif
