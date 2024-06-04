#ifndef PROCESS_H
#define PROCESS_H

#define NUM_PROCESS 5
#define _REMAINING 0
#define _PRIORITY 1

typedef struct Process{
    int processID;
    int arrivalTime;
    int CPUburstTime;
    int IOtime;
    int IOburstTime;
    int priority;
    int remainingTime;
    int returnTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void printProcesses(Process p[], int n);
void createProcesses(Process p[], int n);
void initializeProcesses(Process p[], int n);
void copyProcesses(Process* dest, Process* src, int n);

typedef struct ProcessQueue{
    Process* p[NUM_PROCESS];
    int arrivalTime[NUM_PROCESS];
    int front;
    int rear;
} ProcessQueue;

void initializeQueue(ProcessQueue *q);
void enqueue(ProcessQueue *q, Process* p, int arrivalTime);
Process* dequeue(ProcessQueue *q);
Process* peek(ProcessQueue *q);
void pushPriorityQueue(ProcessQueue *q, Process* p, int arrivalTime, int mode);
Process* popPriorityQueue(ProcessQueue *q, int mode);
Process* peekPriorityQueue(ProcessQueue *q, int mode);

#endif