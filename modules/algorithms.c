#include "algorithms.h"

// First Come First Served
void schedule_FCFS(Process p[], int n, Gantt *gantt) {
    ProcessQueue readyQueue;
    initializeQueue(&readyQueue);
    int currentTime = 0;
    Process* currentProcess = NULL;
    int arrived = 0;
    while(1){
        for(int i = arrived; i < n; i++){
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
                printf("P%d is done at %d\n", currentProcess -> processID, currentTime + 1);
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