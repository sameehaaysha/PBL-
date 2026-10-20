#ifndef PROCESS_H
#define PROCESS_H

#include "../Sameeha/common.h"

void initialize_processes(SystemState *system);
void initialize_resources(SystemState *system);

int set_total_resources(SystemState *system, int resource, int total);

int set_allocation(
    SystemState *system,
    int process,
    int resource,
    int value
);

int set_maximum(
    SystemState *system,
    int process,
    int resource,
    int value
);

void calculate_need(SystemState *system);
void calculate_available(SystemState *system);

int validate_request(
    const SystemState *system,
    int process,
    const int request[]
);

void display_processes(const SystemState *system);
void display_resources(const SystemState *system);

#endif