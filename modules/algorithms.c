#include <stdio.h>
#include <stdlib.h>

// First Come First Served
void schedule_FCFS(Process p[], int n, Gantt *gantt) {
    ProcessQueue readyQueue;
    ProcessQueue waitingQueue;
    int currentTime = 0;
    Process* currentProcess = NULL;
    Process* IOProcess = NULL;
    while(true){
        for(int i = 0; i < n; ++i){
            if(p[i].arrivalTime == currentTime){
                enqueue(&readyQueue, &p[i]);
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


        currentTime++;
    }
}