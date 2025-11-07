#ifndef UTILS_H
#define UTILS_H

#include "process_reader.h"

void print_process_table(const proc_info *procs, int count);
double average_burst(const proc_info *procs, int count);
void sort_by_burst(proc_info *procs, int count);
void sort_by_priority(proc_info *procs, int count);

#endif

