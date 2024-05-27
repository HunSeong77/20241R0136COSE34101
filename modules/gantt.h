#ifndef GANTT_H
#define GANTT_H

#include <stdio.h>
#include <stdlib.h>
#include "./process.h"

#define FCFS 0
#define NON_PREEMPTIVE_SJF 1
#define PREEMPTIVE_SJF 2
#define NON_PREEMPTIVE_PRIORITY 3
#define PREEMPTIVE_PRIORITY 4
#define ROUND_ROBIN 5

#define SIZE 20

typedef struct Gantt{
    Process* p[SIZE];
    int endStamp[SIZE];
    int size;
} Gantt;

void initializeGantt(Gantt* gantt);
void printGantt(Gantt* gantt, int algorithm);


#endif