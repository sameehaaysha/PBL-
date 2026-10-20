#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 20
#define MAX_RESOURCES 10
#define MAX_NAME 50

typedef struct {
    int pid;
    char name[MAX_NAME];

    int allocation[MAX_RESOURCES];
    int maximum[MAX_RESOURCES];
    int need[MAX_RESOURCES];

    int completed;
    int deadlocked;
} Process;

typedef struct {
    int resource_id;
    char name[MAX_NAME];

    int total;
    int available;
} Resource;

typedef struct {
    int process_id;
    int resource_id;
    int amount;
} ResourceRequest;

/* Global system information */
typedef struct {
    int process_count;
    int resource_count;

    Process processes[MAX_PROCESSES];
    Resource resources[MAX_RESOURCES];

    int available[MAX_RESOURCES];

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int maximum[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    /*
     * CURRENT OUTSTANDING REQUEST MATRIX
     *
     * request[i][j] represents the number of instances
     * of resource j that process i is currently waiting
     * to obtain.
     *
     * This is different from need[i][j], which represents
     * the process's remaining maximum requirement.
     */
    int request[MAX_PROCESSES][MAX_RESOURCES];

    int safe_sequence[MAX_PROCESSES];
    int safe_sequence_length;

    int deadlocked[MAX_PROCESSES];
    int deadlocked_count;

} SystemState;


/* Function prototypes */

/* System initialization */
void initialize_system(SystemState *system);

/* Input */
void create_processes(SystemState *system);
void create_resources(SystemState *system);
void enter_allocation_matrix(SystemState *system);
void enter_maximum_matrix(SystemState *system);

/* Matrix calculation */
void calculate_need_matrix(SystemState *system);

/* Display */
void display_need_matrix(SystemState *system);
void display_system_status(SystemState *system);
void display_available_resources(SystemState *system);

/* Resource request */
int request_resources(
    SystemState *system,
    int process_id,
    int request[]
);

/* Banker's Algorithm */
int bankers_algorithm(SystemState *system);

/* Deadlock detection */
int detect_deadlock(SystemState *system);

/* Recovery */
void recover_from_deadlock(SystemState *system);

/* RAG */
void display_resource_allocation_graph(SystemState *system);

/* Utility */
void clear_input_buffer(void);

#endif