#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void print_process_table(const proc_info *procs, int count) {
    printf("\n==============================================\n");
    printf("             ACTIVE USER PROCESSES            \n");
    printf("==============================================\n");
    printf("%-8s %-25s %-10s %-10s %-6s %-6s\n", 
           "PID", "Name", "CPU_SEC", "Burst", "Nice", "UID");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-8d %-25s %-10.2f %-10.2f %-6d %-6d\n",
               procs[i].pid,
               procs[i].name,
               procs[i].cpu_seconds,
               procs[i].burst_estimate,
               procs[i].nice,
               procs[i].uid);
    }

    printf("--------------------------------------------------------------\n\n");
}

double average_burst(const proc_info *procs, int count) {
    if (count == 0) return 0.0;
    double total = 0.0;
    for (int i = 0; i < count; i++)
        total += procs[i].burst_estimate;
    return total / count;
}

void sort_by_burst(proc_info *procs, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (procs[j].burst_estimate > procs[j + 1].burst_estimate) {
                proc_info temp = procs[j];
                procs[j] = procs[j + 1];
                procs[j + 1] = temp;
            }
        }
    }
}

void sort_by_priority(proc_info *procs, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (procs[j].nice > procs[j + 1].nice) {
                proc_info temp = procs[j];
                procs[j] = procs[j + 1];
                procs[j + 1] = temp;
            }
        }
    }
}

