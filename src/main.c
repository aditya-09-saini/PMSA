#include <stdio.h>
#include "../include/pmsa.h"
#include "../include/process_reader.h"
#include "../include/analyzer.h"
#include "../include/scheduler.h"
#include "../include/controller.h"
#include "../include/utils.h"

int main() {
    proc_info procs[MAX_PROCS];
    int count = read_processes(procs, MAX_PROCS);
    printf("Fetched %d processes.\n", count);

    print_process_summary(procs, count);
    system_stats stats = analyze_system(procs, count);
    print_analysis(&stats);

    printf("\nSimulating algorithm: %s\n", stats.recommended_algorithm);
    if (strcmp(stats.recommended_algorithm, "FCFS") == 0)
        simulate_fcfs(procs, count);
    else if (strcmp(stats.recommended_algorithm, "SJF") == 0)
        simulate_sjf(procs, count);
    else if (strcmp(stats.recommended_algorithm, "Priority Scheduling") == 0)
        simulate_priority(procs, count);
    else
        simulate_rr(procs, count, 2.0);

    return 0;
}

