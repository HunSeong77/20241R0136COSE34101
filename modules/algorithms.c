#include <stdio.h>
#include <stdlib.h>

// First Come First Served
void schedule_FCFS(Process p[], int n, Gantt *gantt) {
    ProcessQueue readyQueue;
    int currentTime = 0;
    Process* currentProcess = NULL;
    int arrived = 0;
    while(true){
        for(int i = arrived; i < n; i++){
            if(p[i].arrivalTime == currentTime){
                enqueue(&readyQueue, &p[i]);
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