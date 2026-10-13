#ifndef PRIORITY_RR_H
#define PRIORITY_RR_H

#include "../sameeha/common.h"

void priority_non_preemptive(Process p[], int n);
void priority_preemptive(Process p[], int n);
void round_robin(Process p[], int n, int quantum);

#endif