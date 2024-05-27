#include <stdio.h>
#include <stdlib.h>
#include "process.h"


void printProcess(Process p) {
    printf("Process ID: %d\n", p.processID);
    printf("Arrival Time: %d\n", p.arrivalTime);
    printf("CPU Burst Time: %d\n", p.CPUburstTime);
    printf("IO Burst Time: %d\n", p.IOburstTime);
    printf("Priority: %d\n", p.priority);
    printf("\n");
}

void printProcesses(Process p[], int n) {
    printf("Process name\t| Arrival Time\t| CPU Burst Time\t| IO Burst Time\t| Priority\n");
    printf("--------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t| %d\t\t| %d\t\t\t| %d\t\t| %d\n", p[i].processID, p[i].arrivalTime, p[i].CPUburstTime, p[i].IOburstTime, p[i].priority);
    }
}

void createProcesses(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        // p[i].processID = i+1;
        p[i].arrivalTime = rand() % 10;
        p[i].CPUburstTime = rand() % 10 + 5;
        p[i].IOtime = p[i].CPUburstTime / 2;
        p[i].IOburstTime = rand() % 10;
        p[i].priority = rand() % n + 1;
        p[i].returnTime = 0;
        p[i].waitingTime = 0;
        p[i].turnaroundTime = 0;
    }
    // sort by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (p[i].arrivalTime > p[j].arrivalTime) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    for(int i = 0; i < n; i++){
        p[i].processID = i+1;
    }
}

void initializeProcesses(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].remainingTime = p[i].CPUburstTime;
        p[i].returnTime = 0;
        p[i].waitingTime = 0;
        p[i].turnaroundTime = 0;
    }
}

void initializeQueue(ProcessQueue *q) {
    q->front = 0;
    q->rear = 0;
}

void enqueue(ProcessQueue *q, Process* p, int arrivalTime){
    q->p[q->rear] = p;
    q->arrivalTime[q->rear] = arrivalTime;
    q->rear = (q->rear + 1) % NUM_PROCESS;
}

Process* dequeue(ProcessQueue *q) {
    if(q->front == q->rear) return NULL; // if queue is empty, return NULL.
    Process* p = q->p[q->front];
    q->front = (q->front + 1) % NUM_PROCESS;
    return p;
}

void pushPriorityQueue(ProcessQueue *q, Process* p, int arrivalTime, int mode) {
    int size = q->rear;
    int curr = q->rear;
    int parent = (curr - 1) / 2;
    q->p[curr] = p;
    q->arrivalTime[curr] = arrivalTime;
    q->rear++;
    // while (curr > 0 && q->p[parent]->priority > q->p[curr]->priority) {
    while (curr > 0) {
        if(mode == REMAINING && q->p[parent]->remainingTime <= q->p[curr]->remainingTime) 
            break; // if remaining time is smaller or equal, break.
        if(mode == PRIORITY && q->p[parent]->priority <= q->p[curr]->priority) 
            break; // if priority is smaller or equal, break.
        Process* temp = q->p[parent];
        q->p[parent] = q->p[curr];
        q->p[curr] = temp;
        int tempTime = q->arrivalTime[parent];
        q->arrivalTime[parent] = q->arrivalTime[curr];
        q->arrivalTime[curr] = tempTime;
        curr = parent;
        parent = (curr - 1) / 2;
    }
}

Process* popPriorityQueue(ProcessQueue *q, int mode){
    if(q->rear == 0) return NULL; // if queue is empty, return NULL.
    Process* ret = q->p[0];
    q->p[0] = q->p[q->rear - 1];
    q->arrivalTime[0] = q->arrivalTime[q->rear - 1];
    q->rear--;
    int curr = 0;
    int left = 2 * curr + 1;
    int right = 2 * curr + 2;
    int child = (left < q->rear && right < q->rear) ? (mode == REMAINING ? 
        (q->p[left]->remainingTime < q->p[right]->remainingTime ? left : right) : 
        (q->p[left]->priority < q->p[right]->priority ? left : right)) : 
        (left < q->rear ? left : right);
    while (child < q->rear) {
        if(mode == REMAINING && q->p[curr]->remainingTime <= q->p[child]->remainingTime) 
            break; // if remaining time is smaller or equal, break.
        if(mode == PRIORITY && q->p[curr]->priority <= q->p[child]->priority) 
            break; // if priority is smaller or equal, break.
        Process* temp = q->p[curr];
        q->p[curr] = q->p[child];
        q->p[child] = temp;
        int tempTime = q->arrivalTime[curr];
        q->arrivalTime[curr] = q->arrivalTime[child];
        q->arrivalTime[child] = tempTime;
        curr = child;
        left = 2 * curr + 1;
        right = 2 * curr + 2;
        child = (left < q->rear && right < q->rear) ? (mode == REMAINING ? 
            (q->p[left]->remainingTime < q->p[right]->remainingTime ? left : right) : 
            (q->p[left]->priority < q->p[right]->priority ? left : right)) : 
            (left < q->rear ? left : right);
    }
    return ret;
}