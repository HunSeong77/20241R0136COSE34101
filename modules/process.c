#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    // set seed
    srand(222);
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
    p[0].arrivalTime = 0;
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

void heapify(ProcessQueue* queue, int i, int mode){
    if (queue->rear == 0) return;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int target = i;
    if (left < queue->rear && (mode == _REMAINING ? queue->p[left]->remainingTime < queue->p[target]->remainingTime : queue->p[left]->priority < queue->p[target]->priority)) {
        target = left;
    }
    if (right < queue->rear && (mode == _REMAINING ? queue->p[right]->remainingTime < queue->p[target]->remainingTime : queue->p[right]->priority < queue->p[target]->priority)) {
        target = right;
    }
    if (target != i) {
        Process* temp = queue->p[i];
        queue->p[i] = queue->p[target];
        queue->p[target] = temp;
        int tempTime = queue->arrivalTime[i];
        queue->arrivalTime[i] = queue->arrivalTime[target];
        queue->arrivalTime[target] = tempTime;
        heapify(queue, target, mode);
    }
}

void pushPriorityQueue(ProcessQueue *q, Process* p, int arrivalTime, int mode) {
    int size = q->rear;
    if(size == 0){
        q->p[0] = p;
        q->arrivalTime[0] = arrivalTime;
        q->rear++;
        return;
    }
    q->p[size] = p;
    q->arrivalTime[size] = arrivalTime;
    q->rear++;
    for(int i = (q->rear)/2-1 ; i >= 0; i--)
        heapify(q, i, mode);
}

Process* popPriorityQueue(ProcessQueue *q, int mode){
    if(q->rear == 0) return NULL; // if queue is empty, return NULL.
    Process* ret = q->p[0];
    q->rear--;
    q->p[0] = q->p[q->rear];
    q->arrivalTime[0] = q->arrivalTime[q->rear];
    for(int i = (q->rear)/2-1 ; i >= 0; i--)
        heapify(q, i, mode);
    return ret;
}

Process* peekPriorityQueue(ProcessQueue *q, int mode){
    if(q->rear == 0) return NULL; // if queue is empty, return NULL.
    return q->p[0];
}