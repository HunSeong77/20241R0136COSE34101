#include "algorithms.h"

// First Come First Served
void schedule_FCFS(Process p[], int n, Gantt *gantt) {
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    int arrived = 0;
    while(1){
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                enqueue(&readyQueue, &p[i], currentTime);
                arrived++;
            }
        }
        if(currentProcess == NULL){
            currentProcess = dequeue(&readyQueue);
        }
        if(currentProcess != NULL){
            currentProcess -> remainingTime--;
            if(currentProcess -> remainingTime == 0){
                currentProcess -> returnTime = currentTime + 1;
                currentProcess -> turnaroundTime = currentProcess -> returnTime - currentProcess -> arrivalTime;
                currentProcess -> waitingTime =  currentProcess -> turnaroundTime - currentProcess -> CPUburstTime;
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime + 1;
                gantt -> size++;
                currentProcess = dequeue(&readyQueue);
            }
        }
        if(currentProcess == NULL && readyQueue.front == readyQueue.rear && arrived == n) break;
        currentTime++;
    }
}

// Non-Preemptive Shortest Job First
void schedule_NPSJF(Process p[], int n, Gantt *gantt){
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    int arrived = 0;
    while(1){
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                pushPriorityQueue(&readyQueue, &p[i], currentTime, _REMAINING);
                arrived++;
            }
        }
        if(currentProcess == NULL){
            currentProcess = popPriorityQueue(&readyQueue, _REMAINING);
        }
        if(currentProcess != NULL){
            currentProcess -> remainingTime--;
            if(currentProcess -> remainingTime == 0){
                currentProcess -> returnTime = currentTime + 1;
                currentProcess -> turnaroundTime = currentProcess -> returnTime - currentProcess -> arrivalTime;
                currentProcess -> waitingTime =  currentProcess -> turnaroundTime - currentProcess -> CPUburstTime;
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime + 1;
                gantt -> size++;
                currentProcess = popPriorityQueue(&readyQueue, _REMAINING);
            }
        }
        if(currentProcess == NULL && readyQueue.front == readyQueue.rear && arrived == n) break;
        currentTime++;
    }
}

void schedule_SJF(Process p[], int n, Gantt *gantt){
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    int arrived = 0;
    while(1){
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                pushPriorityQueue(&readyQueue, &p[i], currentTime, _REMAINING);
                arrived++;
            }
        }
        if(currentProcess == NULL){
            currentProcess = popPriorityQueue(&readyQueue, _REMAINING);
        }
        if(currentProcess != NULL){
            currentProcess -> remainingTime--;
            Process *nextProcess = peekPriorityQueue(&readyQueue, _REMAINING);
            if(nextProcess != NULL && nextProcess -> remainingTime < currentProcess -> remainingTime){
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime + 1;
                gantt -> size++;
                pushPriorityQueue(&readyQueue, currentProcess, currentTime, _REMAINING);
                currentProcess = popPriorityQueue(&readyQueue, _REMAINING);
            }
            if(currentProcess -> remainingTime == 0){
                currentProcess -> returnTime = currentTime + 1;
                currentProcess -> turnaroundTime = currentProcess -> returnTime - currentProcess -> arrivalTime;
                currentProcess -> waitingTime =  currentProcess -> turnaroundTime - currentProcess -> CPUburstTime;
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime + 1;
                gantt -> size++;
                currentProcess = popPriorityQueue(&readyQueue, _REMAINING);
            }
        }
        if(currentProcess == NULL && readyQueue.front == readyQueue.rear && arrived == n) break;
        currentTime++;
    }
}