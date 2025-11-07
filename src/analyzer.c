#include <stdio.h>
#include <string.h>
#include "../include/analyzer.h"
#include "../include/utils.h"

system_stats analyze_system(const proc_info *procs, int count) {
    system_stats stats = {0};
    if (count == 0) return stats;

    stats.active_procs = count;
    stats.avg_burst = average_burst(procs, count);

    int min_n = 20, max_n = -20;
    for (int i = 0; i < count; i++) {
        if (procs[i].nice < min_n) min_n = procs[i].nice;
        if (procs[i].nice > max_n) max_n = procs[i].nice;
    }
    stats.min_nice = min_n;
    stats.max_nice = max_n;
    stats.cpu_load = (double)(rand() % 100);

    recommend_algorithm(&stats);
    return stats;
}

void recommend_algorithm(system_stats *stats) {
    if (stats->cpu_load > 80)
        strcpy(stats->recommended_algorithm, "Round Robin");
    else if (stats->avg_burst < 5)
        strcpy(stats->recommended_algorithm, "SJF");
    else if (stats->min_nice < 0)
        strcpy(stats->recommended_algorithm, "Priority Scheduling");
    else
        strcpy(stats->recommended_algorithm, "FCFS");
}

void print_analysis(const system_stats *stats) {
    printf("\n===== SYSTEM ANALYSIS =====\n");
    printf("Active Processes: %d\n", stats->active_procs);
    printf("Average Burst Time: %.2f\n", stats->avg_burst);
    printf("CPU Load: %.2f%%\n", stats->cpu_load);
    printf("Priority Range: %d to %d\n", stats->min_nice, stats->max_nice);
    printf("Recommended Algorithm: %s\n", stats->recommended_algorithm);
}
