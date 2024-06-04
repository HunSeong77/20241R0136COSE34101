#include "algorithms.h"

/*
    psuedo code for all of the scheduling algorithms

    Initialize ready queue
    Initialize current time
    while no process is in the ready queue or all processes have not arrived or there is current process
        for each process in the process list
            if the process has arrived
                add the process to the ready queue
        if there is no current process
            get the next process from the ready queue
            set the current process to the next process
        if there is a current process
            if the change criteria is met
                stamp the current process
                change the current process to the next process
            consume current process' CPU burst time
        increment current time
*/

// First Come First Served
void schedule_FCFS(Process p[], int n, Gantt *gantt){
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    Process* nextProcess = NULL;
    int arrived = 0;
    while(!((readyQueue.front == readyQueue.rear) && (arrived == n) && (currentProcess == NULL))){
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                enqueue(&readyQueue, &p[i], currentTime);
                arrived++;
            }
        }
        if(currentProcess == NULL){
            nextProcess = dequeue(&readyQueue);
            currentProcess = nextProcess;
            if(currentProcess != NULL){
                gantt -> p[gantt -> size] = NULL;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
            }
        }
        if(currentProcess != NULL){
            nextProcess = peek(&readyQueue);
            if(currentProcess -> remainingTime == 0){ // change criteria : consume all CPU burst time
                currentProcess -> returnTime = currentTime; // stamp the current process
                currentProcess -> turnaroundTime = currentProcess -> returnTime - currentProcess -> arrivalTime;
                currentProcess -> waitingTime =  currentProcess -> turnaroundTime - currentProcess -> CPUburstTime;
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
                currentProcess = nextProcess; // change the current process to the next process
                dequeue(&readyQueue);
            }
            if(currentProcess != NULL)
                currentProcess -> remainingTime--; // consume CPU burst time
        }
        currentTime++; // increment current time
    }
}

// Non-Preemptive Shortest Job First
void schedule_NPSJF(Process p[], int n, Gantt *gantt){
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    Process* nextProcess = NULL;
    int arrived = 0;
    while(!((readyQueue.front == readyQueue.rear) && (arrived == n) && (currentProcess == NULL))){
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                pushPriorityQueue(&readyQueue, &p[i], currentTime, _REMAINING);
                arrived++;
            }
        }
        if(currentProcess == NULL){
            nextProcess = popPriorityQueue(&readyQueue, _REMAINING);
            currentProcess = nextProcess;
            if(currentProcess != NULL){
                gantt -> p[gantt -> size] = NULL;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
            }
        }
        if(currentProcess != NULL){
            nextProcess = peekPriorityQueue(&readyQueue, _REMAINING);
            if(currentProcess -> remainingTime == 0){ // change criteria : consume all CPU burst time
                currentProcess -> returnTime = currentTime; // stamp the current process
                currentProcess -> turnaroundTime = currentProcess -> returnTime - currentProcess -> arrivalTime;
                currentProcess -> waitingTime =  currentProcess -> turnaroundTime - currentProcess -> CPUburstTime;
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
                currentProcess = nextProcess; // change the current process to the next process
                popPriorityQueue(&readyQueue, _REMAINING);
            }
            if(currentProcess != NULL)
                currentProcess -> remainingTime--; // consume CPU burst time
        }
        currentTime++; // increment current time
    }
}

// Preemptive Shortest Job First
void schedule_SJF(Process p[], int n, Gantt *gantt){
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    Process* nextProcess = NULL;
    int arrived = 0;
    while(!((readyQueue.front == readyQueue.rear) && (arrived == n) && (currentProcess == NULL))){
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                pushPriorityQueue(&readyQueue, &p[i], currentTime, _REMAINING);
                arrived++;
            }
        }
        if(currentProcess == NULL){
            nextProcess = popPriorityQueue(&readyQueue, _REMAINING);
            currentProcess = nextProcess;
            if(currentProcess != NULL){
                gantt -> p[gantt -> size] = NULL;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
            }
        }
        if(currentProcess != NULL){
            nextProcess = peekPriorityQueue(&readyQueue, _REMAINING);
            if((currentProcess -> remainingTime == 0) ||
            (nextProcess != NULL && nextProcess -> remainingTime < currentProcess -> remainingTime)){ // change criteria : consume all CPU burst time
                currentProcess -> returnTime = currentTime; // stamp the current process
                currentProcess -> turnaroundTime = currentProcess -> returnTime - currentProcess -> arrivalTime;
                currentProcess -> waitingTime =  currentProcess -> turnaroundTime - currentProcess -> CPUburstTime;
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
                if(currentProcess -> remainingTime != 0)
                    pushPriorityQueue(&readyQueue, currentProcess, currentTime, _REMAINING);
                currentProcess = nextProcess; // change the current process to the next process
                popPriorityQueue(&readyQueue, _REMAINING);
            }
            if(currentProcess != NULL)
                currentProcess -> remainingTime--; // consume CPU burst time
        }
        currentTime++; // increment current time
    }
}

// Non-Preemptive Priority
void schedule_NPPRIORITY(Process p[], int n, Gantt *gantt){
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    Process* nextProcess = NULL;
    int arrived = 0;
    while(!((readyQueue.front == readyQueue.rear) && (arrived == n) && (currentProcess == NULL))){
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                pushPriorityQueue(&readyQueue, &p[i], currentTime, _PRIORITY);
                arrived++;
            }
        }
        if(currentProcess == NULL){
            nextProcess = popPriorityQueue(&readyQueue, _PRIORITY);
            currentProcess = nextProcess;
            if(currentProcess != NULL){
                gantt -> p[gantt -> size] = NULL;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
            }
        }
        if(currentProcess != NULL){
            nextProcess = peekPriorityQueue(&readyQueue, _PRIORITY);
            if(currentProcess -> remainingTime == 0){ // change criteria : consume all CPU burst time
                currentProcess -> returnTime = currentTime; // stamp the current process
                currentProcess -> turnaroundTime = currentProcess -> returnTime - currentProcess -> arrivalTime;
                currentProcess -> waitingTime =  currentProcess -> turnaroundTime - currentProcess -> CPUburstTime;
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
                currentProcess = nextProcess; // change the current process to the next process
                popPriorityQueue(&readyQueue, _PRIORITY);
            }
            if(currentProcess != NULL)
                currentProcess -> remainingTime--; // consume CPU burst time
        }
        currentTime++; // increment current time
    }
}

// Preemptive Priority
void schedule_PRIORITY(Process p[], int n, Gantt *gantt){
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    Process* nextProcess = NULL;
    int arrived = 0;
    while(!((readyQueue.front == readyQueue.rear) && (arrived == n) && (currentProcess == NULL))){
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                pushPriorityQueue(&readyQueue, &p[i], currentTime, _PRIORITY);
                arrived++;
            }
        }
        if(currentProcess == NULL){
            nextProcess = popPriorityQueue(&readyQueue, _PRIORITY);
            currentProcess = nextProcess;
            if(currentProcess != NULL){
                gantt -> p[gantt -> size] = NULL;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
            }
        }
        if(currentProcess != NULL){
            nextProcess = peekPriorityQueue(&readyQueue, _PRIORITY);
            if((currentProcess -> remainingTime == 0) ||
            (nextProcess != NULL && nextProcess -> priority < currentProcess -> priority)){ // change criteria : consume all CPU burst time
                currentProcess -> returnTime = currentTime; // stamp the current process
                currentProcess -> turnaroundTime = currentProcess -> returnTime - currentProcess -> arrivalTime;
                currentProcess -> waitingTime =  currentProcess -> turnaroundTime - currentProcess -> CPUburstTime;
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
                if(currentProcess -> remainingTime != 0)
                    pushPriorityQueue(&readyQueue, currentProcess, currentTime, _PRIORITY);
                currentProcess = nextProcess; // change the current process to the next process
                popPriorityQueue(&readyQueue, _PRIORITY);
            }
            if(currentProcess != NULL)
                currentProcess -> remainingTime--; // consume CPU burst time
        }
        currentTime++; // increment current time
    }
}

// Round Robin
void schedule_RR(Process p[], int n, Gantt* gantt, int quantum){
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    Process* nextProcess = NULL;
    int arrived = 0;
    int quantumCounter = 0;
    while(!((readyQueue.front == readyQueue.rear) && (arrived == n) && (currentProcess == NULL) && (nextProcess == NULL))){
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                enqueue(&readyQueue, &p[i], currentTime);
                arrived++;
            }
        }
        if(currentProcess == NULL){
            nextProcess = dequeue(&readyQueue);
            currentProcess = nextProcess;
            if(currentProcess != NULL){
                gantt -> p[gantt -> size] = NULL;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
            }
            quantumCounter = 0; // reset quantum counter
        }
        if(currentProcess != NULL){
            nextProcess = peek(&readyQueue);
            if((currentProcess -> remainingTime == 0) ||
                ((quantumCounter >= quantum) && (nextProcess != NULL))){ // change criteria : consume all CPU burst time or quantum is reached and there is a ready process
                currentProcess -> returnTime = currentTime; // stamp the current process
                currentProcess -> turnaroundTime = currentProcess -> returnTime - currentProcess -> arrivalTime;
                currentProcess -> waitingTime =  currentProcess -> turnaroundTime - currentProcess -> CPUburstTime;
                gantt -> p[gantt -> size] = currentProcess;
                gantt -> endStamp[gantt -> size] = currentTime;
                gantt -> size++;
                dequeue(&readyQueue);
                if(currentProcess -> remainingTime > 0)
                    enqueue(&readyQueue, currentProcess, currentTime);
                currentProcess = nextProcess; // change the current process to the next process
                quantumCounter = 0; // reset quantum counter
            }
            if(currentProcess != NULL){
                currentProcess -> remainingTime--; // consume CPU burst time
                quantumCounter++;
            }
        }
        currentTime++; // increment current time
    }
}