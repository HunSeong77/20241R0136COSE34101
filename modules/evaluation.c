#include "evaluation.h"

void printResult(Process p[], int n, int algorithm, int range, int header){
    double avgTurnaroundTime = 0;
    double avgWaitingTime = 0;
    char* algorithmName;
    switch(algorithm){
        case FCFS:
            algorithmName = "FCFS"; break;
        case NPSJF:
            algorithmName = "Non-Preemptive SJF"; break;
        case SJF:
            algorithmName = "Preemptive SJF"; break;
        case NPPRIORITY:
            algorithmName = "Non-Preemptive Priority"; break;
        case PRIORITY:
            algorithmName = "Preemptive Priority"; break;
        case RR:
            algorithmName = "Round Robin"; break;
    }
    if(range == TOTAL){
        if(header){
            printf("Process ID | Arrival Time | Burst Time | Return Time | Turnaround Time | Waiting Time\n");
            printf("-----------|--------------|------------|-------------|----------------|-------------\n");
        }
        for(int i = 0; i < n; i++){
            printf("P%d         | %2d           | %2d         | %2d             | %2d             | %2d\n", p[i].processID, p[i].arrivalTime, p[i].CPUburstTime, p[i].returnTime, p[i].turnaroundTime, p[i].waitingTime);
            avgTurnaroundTime += p[i].turnaroundTime;
            avgWaitingTime += p[i].waitingTime;
        }
        avgTurnaroundTime /= n;
        avgWaitingTime /= n;
            printf("Average    | --           | --         | --             | %3.1f           | %3.1f\n", avgTurnaroundTime, avgWaitingTime);
    }
    else if (range == AVERAGE){
        for(int i = 0; i < n; i++){
            avgTurnaroundTime += p[i].turnaroundTime;
            avgWaitingTime += p[i].waitingTime;
        }
        avgTurnaroundTime /= n;
        avgWaitingTime /= n;
        if(header){
            printf(" Algorithm                 | Avg Waiting Time | Avg Turnaround Time\n");
            printf("---------------------------|------------------|--------------------\n");
        }
        printf(" %-25s |   %3.1f           | %3.1f\n", algorithmName, avgWaitingTime, avgTurnaroundTime);
    }
}