#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "pmsa.h"

// Data structure for simulated scheduling output
typedef struct {
    pid_t pid;
    char name[NAME_LEN];
    double burst_time;
    double waiting_time;
    double turnaround_time;
} schedule_result;

// Scheduling algorithms
void simulate_fcfs(const proc_info *procs, int count);
void simulate_sjf(const proc_info *procs, int count);
void simulate_rr(const proc_info *procs, int count, double quantum);
void simulate_priority(const proc_info *procs, int count);

// Displays schedule results (generic function)
void print_schedule_results(const schedule_result *results, int count, const char *algorithm);

#endif

