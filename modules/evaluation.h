#ifndef EVALUATION_H
#define EVALUATION_H

#include <stdio.h>
#include "process.h"
#include "gantt.h"

#define TOTAL 0
#define AVERAGE 1

void printResult(Process p[], int n, int algorithm, int range, int header);

#endif