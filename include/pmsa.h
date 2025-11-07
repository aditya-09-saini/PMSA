#ifndef PMSA_H
#define PMSA_H

#include <sys/types.h>
#include <time.h>

#define MAX_PROCS 256
#define NAME_LEN 256
#define ALG_NAME_LEN 32

typedef struct {
    pid_t pid;                  // Process ID
    char name[NAME_LEN];        // Process name
    char state;                 // Process state (R, S, Z, etc.)
    uid_t uid;                  // User ID of the owner
    double cpu_seconds;         // Total CPU time used
    int nice;                   // Process priority (nice value)
    double burst_estimate;      // Estimated CPU burst (for SJF)
} proc_info;

typedef struct {
    double cpu_load;
    int active_procs;
    double avg_burst;
    int min_nice;
    int max_nice;
    char recommended_algorithm[ALG_NAME_LEN];
} system_stats;

#endif

