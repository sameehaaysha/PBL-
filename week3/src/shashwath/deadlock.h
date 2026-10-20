#ifndef DEADLOCK_H
#define DEADLOCK_H

#include "../Sameeha/common.h"

int bankers_algorithm(SystemState *s);
int detect_deadlock(SystemState *s);
int request_resources(SystemState *s, int pid, int req[]);
void recover_from_deadlock(SystemState *s);

#endif