#include "gantt.h"

void initializeGantt(Gantt* gantt){
    gantt -> size = 0;
}

void printGantt(Gantt* gantt, int algorithm){
    printf("                           ");
    for(int i = 0; i <= gantt->endStamp[gantt->size-1]; i++){
        printf("-");
    }
    printf("\n");

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
        int pre_blank = (len - 3) / 2;
        int post_blank = len - 3 - pre_blank;
        for(int j = 0; j < pre_blank; j++){
            printf(" ");
        }
        printf("P%d", gantt->p[i]->processID);
        for(int j = 0; j < post_blank; j++){
            printf(" ");
        }
        printf("|");
    }
    printf("\n");

    printf("                           ");
    int j = 0;
    printf("0");
    for(int i = 1; i <= gantt->endStamp[gantt->size-1]; i++){
        if(j <= gantt->size && i == gantt->endStamp[j]){
            j++;
            printf("\b%2d", i);
        }else{
            printf("-");
        }
    }
    printf("\n");
}