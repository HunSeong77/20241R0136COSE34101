#ifndef GANTT_H
#define GANTT_H

#include <stdio.h>
#include <stdlib.h>
#include "./process.h"

#define FCFS 0
#define NPSJF 1
#define SJF 2
#define NPPRIORITY 3
#define PRIORITY 4
#define RR 5

#define SIZE 30

typedef struct Gantt{
    Process* p[SIZE];
    int endStamp[SIZE];
    int size;
} Gantt;

void initializeGantt(Gantt* gantt);
void printGantt(Gantt* gantt, int algorithm);


#endif