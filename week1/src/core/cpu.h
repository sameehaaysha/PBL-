#ifndef CPU_H
#define CPU_H

typedef struct
{
    int acc;
    int pc;
    int active;
} Processor;

void execute_instruction(Processor *cpu, char instruction[]);

#endif