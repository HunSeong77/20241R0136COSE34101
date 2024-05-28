#include <stdio.h>
#include <stdlib.h>
#include "./modules/process.h"
#include "./modules/gantt.h"
#include "./modules/algorithms.h"

#define NUM_PROCESS 5

int main(){
    Process process[NUM_PROCESS];
    createProcesses(process, NUM_PROCESS);
    printProcesses(process, NUM_PROCESS);
    Gantt gantt;
    printf("\n");

    // Schedule FCFS
    initializeProcesses(process, NUM_PROCESS);
    initializeGantt(&gantt);
    schedule_FCFS(process, NUM_PROCESS, &gantt);
    printGantt(&gantt, FCFS);

    // Schedule Non-preemptive SJF
    initializeProcesses(process, NUM_PROCESS);
    initializeGantt(&gantt);
    schedule_NPSJF(process, NUM_PROCESS, &gantt);
    printGantt(&gantt, NPSJF);

    // Schedule Preemptive SJF
    initializeProcesses(process, NUM_PROCESS);
    initializeGantt(&gantt);
    schedule_SJF(process, NUM_PROCESS, &gantt);
    printGantt(&gantt, SJF);

    // Schedule Non-preemptive Priority
    initializeProcesses(process, NUM_PROCESS);
    initializeGantt(&gantt);
    schedule_NPPRIORITY(process, NUM_PROCESS, &gantt);
    printGantt(&gantt, NPPRIORITY);

    // Schedule Preemptive Priority
    initializeProcesses(process, NUM_PROCESS);
    initializeGantt(&gantt);
    schedule_PRIORITY(process, NUM_PROCESS, &gantt);
    printGantt(&gantt, PRIORITY);
    return 0;
}