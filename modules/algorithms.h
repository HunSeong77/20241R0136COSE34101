#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include "./process.h"
#include "./gantt.h"

void schedule_FCFS(Process p[], int n, Gantt* gantt);
void schedule_NPSJF(Process p[], int n, Gantt* gantt);
void schedule_SJF(Process p[], int n, Gantt* gantt);
void schedule_NPPRIORITY(Process p[], int n, Gantt* gantt);
void schedule_PRIORITY(Process p[], int n, Gantt* gantt);

#endif