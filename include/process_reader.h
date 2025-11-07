#ifndef PROCESS_READER_H
#define PROCESS_READER_H

#include "pmsa.h"

// Reads process data from /proc into an array of proc_info structs
int read_processes(proc_info *procs, int max_procs);

// Prints a brief summary of all running processes
void print_process_summary(const proc_info *procs, int count);

#endif

