#include "gantt.h"

int quantum = 4;

void initializeGantt(Gantt* gantt){
    gantt -> size = 0;
}

void printGantt(Gantt* gantt, int algorithm){
    int num_blanks[SIZE];
    for(int i = 0; i < gantt->size; i++){
        int len = gantt->endStamp[i] - (i == 0 ? 0 : gantt->endStamp[i-1]);
        num_blanks[i] = len == 0 ? -1 : (len < 3 ? 0 : (len < 10 ? (len - 3) / 2 : 3));
    }
    printf("                           ");
    for(int i = 0; i < gantt->size; i++){
        if(num_blanks[i] >= 0){
            for(int j = 0; j < num_blanks[i]; j++){
                printf("__");
            }
            printf("___");
        }
    }
    printf("_\n");

    switch(algorithm){
        case FCFS:
            printf(" FCFS :                    "); break;
        case NPSJF:
            printf(" Non-Preemptive SJF :      "); break;
        case SJF:
            printf(" Preemptive SJF :          "); break;
        case NPPRIORITY:
            printf(" Non-Preemptive Priority : "); break;
        case PRIORITY:
            printf(" Preemptive Priority :     "); break;
        case RR:
            printf(" Round Robin (%d):          ", quantum); break;
    }

    printf("|");
    for(int i = 0; i < gantt->size; i++){
        if(num_blanks[i] < 0) continue;
        for(int j = 0; j < num_blanks[i]; j++)
            printf(" ");

        if(gantt->p[i] != NULL)
            printf("P%d", gantt->p[i]->processID);
        else
            printf("--");
        
        for(int j = 0; j < num_blanks[i]; j++)
            printf(" ");
        
        printf("|");
    }
    printf("\n");

    printf("                           ");
    int j = 0;
    printf("0-");
    for(int i = 0; i < gantt->size; i++){
        if(num_blanks[i] < 0) continue;
        for(int j = 0; j < num_blanks[i]; j++)
            printf("--");
        int time = gantt->endStamp[i];
        if(time < 10)
            printf("-%d-", time);
        else if (time < 100)
            printf("-%d", time);
        else
            printf("%d", time);
    }
    printf("\n");
}