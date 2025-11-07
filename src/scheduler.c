#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/scheduler.h"
#include "../include/utils.h"

void simulate_fcfs(const proc_info *procs, int count) {
    printf("\n[FCFS Simulation]\n");
    sort_by_burst((proc_info *)procs, count); // same as arrival order mock
    for (int i = 0; i < count; i++)
        printf("%d (%s) executed.\n", procs[i].pid, procs[i].name);
}

void simulate_sjf(const proc_info *procs, int count) {
    printf("\n[SJF Simulation]\n");
    proc_info *copy = malloc(count * sizeof(proc_info));
    memcpy(copy, procs, count * sizeof(proc_info));
    sort_by_burst(copy, count);
    for (int i = 0; i < count; i++)
        printf("%d (%s): %.2f burst\n", copy[i].pid, copy[i].name, copy[i].burst_estimate);
    free(copy);
}

void simulate_rr(const proc_info *procs, int count, double quantum) {
    printf("\n[Round Robin Simulation] (quantum=%.2f)\n", quantum);
    for (int i = 0; i < count; i++)
        printf("%d (%s): processed for %.2fs\n", procs[i].pid, procs[i].name, quantum);
}

void simulate_priority(const proc_info *procs, int count) {
    printf("\n[Priority Scheduling Simulation]\n");
    proc_info *copy = malloc(count * sizeof(proc_info));
    memcpy(copy, procs, count * sizeof(proc_info));
    sort_by_priority(copy, count);
    for (int i = 0; i < count; i++)
        printf("%d (%s): nice=%d\n", copy[i].pid, copy[i].name, copy[i].nice);
    free(copy);
}

