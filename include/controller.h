#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "pmsa.h"

// Safely adjusts process priority using nice()
int change_process_priority(pid_t pid, int new_nice);

// Sends signals (pause, resume, terminate) to processes
int send_signal_to_process(pid_t pid, int signal);

// Displays info about controlled process
void print_control_action(pid_t pid, const char *action);

#endif

