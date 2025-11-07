#ifndef ANALYZER_H
#define ANALYZER_H

#include "pmsa.h"

// Analyzes system metrics (CPU load, burst times, priorities)
system_stats analyze_system(const proc_info *procs, int count);

// Determines best scheduling algorithm based on metrics
void recommend_algorithm(system_stats *stats);

// Displays the analysis and recommendation
void print_analysis(const system_stats *stats);

#endif
