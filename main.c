#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./modules/process.h"
#include "./modules/gantt.h"
#include "./modules/algorithms.h"
#include "./modules/evaluation.h"

#define NUM_PROCESS 5

Process src_process[NUM_PROCESS];
Process FCFS_process[NUM_PROCESS];
Process NPSJF_process[NUM_PROCESS];
Process SJF_process[NUM_PROCESS];
Process NPPRIORITY_process[NUM_PROCESS];
Process PRIORITY_process[NUM_PROCESS];
Process RR_process[NUM_PROCESS];
Gantt FCFS_gantt;
Gantt NPSJF_gantt;
Gantt SJF_gantt;
Gantt NPPRIORITY_gantt;
Gantt PRIORITY_gantt;
Gantt RR_gantt;
extern int quantum;

void schedule(){
    // Schedule FCFS
    copyProcesses(FCFS_process, src_process, NUM_PROCESS);
    initializeGantt(&FCFS_gantt);
    schedule_FCFS(FCFS_process, NUM_PROCESS, &FCFS_gantt);

    // Schedule NPSJF
    copyProcesses(NPSJF_process, src_process, NUM_PROCESS);
    initializeGantt(&NPSJF_gantt);
    schedule_NPSJF(NPSJF_process, NUM_PROCESS, &NPSJF_gantt);

    // Schedule SJF
    copyProcesses(SJF_process, src_process, NUM_PROCESS);
    initializeGantt(&SJF_gantt);
    schedule_SJF(SJF_process, NUM_PROCESS, &SJF_gantt);

    // Schedule NPPRIORITY
    copyProcesses(NPPRIORITY_process, src_process, NUM_PROCESS);
    initializeGantt(&NPPRIORITY_gantt);
    schedule_NPPRIORITY(NPPRIORITY_process, NUM_PROCESS, &NPPRIORITY_gantt);

    // Schedule PRIORITY
    copyProcesses(PRIORITY_process, src_process, NUM_PROCESS);
    initializeGantt(&PRIORITY_gantt);
    schedule_PRIORITY(PRIORITY_process, NUM_PROCESS, &PRIORITY_gantt);

    // Schedule RR
    copyProcesses(RR_process, src_process, NUM_PROCESS);
    initializeGantt(&RR_gantt);
    schedule_RR(RR_process, NUM_PROCESS, &RR_gantt, quantum);
}

void configure_process(){
    char command = ' ';
    while(command != 'q'){
        write(1, "\033[1;1H\033[2J", 10); // Clear screen
        printProcesses(src_process, NUM_PROCESS);
        printf("\n");
        printf("Enter process ID to configure or q to quit: P");
        command = getchar();
        if(command == 'q'){
            break;
        }
        int processID = command - '1';
        if(processID < 0 || processID >= NUM_PROCESS){
            continue;
        }
        printf("Enter arrival time: ");
        scanf("%d", &src_process[processID].arrivalTime);
        printf("Enter CPU burst time: ");
        scanf("%d", &src_process[processID].CPUburstTime);
        printf("Enter I/O burst time: ");
        scanf("%d", &src_process[processID].IOburstTime);
        printf("Enter priority: ");
        scanf("%d", &src_process[processID].priority);
    }
}

void configure_quantum(){
    printf("Current time quantum: %d\n", quantum);
    printf("Enter the new time quantum: ");
    scanf("%d", &quantum);
}

void configure(){
    char command = ' ';
    while(command != 'q'){
        write(1, "\033[1;1H\033[2J", 10); // Clear screen
        printf("p : Configure Processes \t");
        printf("t : Configure Time Quantum\n");
        printf("q : Quit\n");
        command = getchar();
        if(command == 'p'){
            configure_process();
        }
        else if (command == 't'){
            configure_quantum();
        }
    }
}

int main(){
    createProcesses(src_process, NUM_PROCESS);
    initializeProcesses(src_process, NUM_PROCESS);

    schedule();

    char command = ' ';

    int prt_processes = 0;
    int prt_gantt = 0;
    int prt_result = 0;

    while(command != 'q'){
        write(1, "\033[1;1H\033[2J", 10); // Clear screen
        if(prt_processes){
            printProcesses(src_process, NUM_PROCESS);
            printf("\n");
        }
        if(prt_gantt){
            printGantt(&FCFS_gantt, FCFS);
            printGantt(&NPSJF_gantt, NPSJF);
            printGantt(&SJF_gantt, SJF);
            printGantt(&NPPRIORITY_gantt, NPPRIORITY);
            printGantt(&PRIORITY_gantt, PRIORITY);
            printGantt(&RR_gantt, RR);
            printf("\n");
        }
        if(prt_result){
            printResult(FCFS_process, NUM_PROCESS, FCFS, AVERAGE, 1);
            printResult(NPSJF_process, NUM_PROCESS, NPSJF, AVERAGE, 0);
            printResult(SJF_process, NUM_PROCESS, SJF, AVERAGE, 0);
            printResult(NPPRIORITY_process, NUM_PROCESS, NPPRIORITY, AVERAGE, 0);
            printResult(PRIORITY_process, NUM_PROCESS, PRIORITY, AVERAGE, 0);
            printResult(RR_process, NUM_PROCESS, RR, AVERAGE, 0);
            printf("\n");
        }
        printf("p: Print Processes\t");
        printf("g: Print Gantt Chart\t");
        printf("r: Print Result\n");
        printf("c: Configure\t\t");
        printf("q: Quit\n");
        command = getchar();
        if(command == 'p'){
            prt_processes = !prt_processes;
        }
        else if(command == 'g'){
            prt_gantt = !prt_gantt;
        }
        else if(command == 'r'){
            prt_result = !prt_result;
        }
        else if (command == 'c'){
            configure();
            schedule();
        }
    }


    return 0;
}