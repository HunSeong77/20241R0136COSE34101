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

typedef struct{
    Process* p[SIZE];
    int endStamp[SIZE];
    int size;
} Gantt;

void printGantt(Gantt* gantt, int algorithm){
    printf("                           ");
    for(int i = 0; i < gantt->endStamp[gantt->size-1]; i++){
        printf("-");
    }

    switch(algorithm){
        case FCFS:
            printf(" FCFS :                    "); break;
        case NON_PREEMPTIVE_SJF:
            printf(" Non-Preemptive SJF :      "); break;
        case PREEMPTIVE_SJF:
            printf(" Preemptive SJF :          "); break;
        case NON_PREEMPTIVE_PRIORITY:
            printf(" Non-Preemptive Priority : "); break;
        case PREEMPTIVE_PRIORITY:
            printf(" Preemptive Priority :     "); break;
        case ROUND_ROBIN:
            printf(" Round Robin :             "); break;
    }

    printf("|");
    for(int i = 0; i < gantt->size; i++){
        int len = i == 0 ? gantt->endStamp[i] : gantt->endStamp[i] - gantt->endStamp[i-1];
        int pre_blank = (len - 4) / 2;
        int post_blank = len - 4 - pre_blank;
        for(int j = 0; j < pre_blank; j++){
            printf(" ");
        }
        printf("P%d", gantt->p[i]->processID);
        for(int j = 0; j < post_blank; j++){
            printf(" ");
        }
        printf("|");
    }

    printf("                           ");
    for(int i = 0; i < gantt->endStamp[gantt->size-1]; i++){
        printf("-");
    }
}