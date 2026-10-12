
#ifndef FCFS_SJF_H
#define FCFS_SJF_H

#include "common.h"

void run_fcfs(Process processes[], int n,
              Segment gantt[], int *segment_count);

void run_sjf_non_preemptive(Process processes[], int n,
                            Segment gantt[], int *segment_count);

void run_sjf_preemptive(Process processes[], int n,
                        Segment gantt[], int *segment_count);

#endif
