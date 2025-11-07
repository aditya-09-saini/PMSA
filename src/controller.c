#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/resource.h>
#include "../include/controller.h"

int change_process_priority(pid_t pid, int new_nice) {
    if (setpriority(PRIO_PROCESS, pid, new_nice) == -1) {
        perror("Failed to change priority");
        return -1;
    }
    print_control_action(pid, "priority changed");
    return 0;
}

int send_signal_to_process(pid_t pid, int signal) {
    if (kill(pid, signal) == -1) {
        perror("Signal failed");
        return -1;
    }
    char action[32];
    if (signal == SIGSTOP) strcpy(action, "paused");
    else if (signal == SIGCONT) strcpy(action, "resumed");
    else if (signal == SIGTERM) strcpy(action, "terminated");
    else strcpy(action, "signaled");
    print_control_action(pid, action);
    return 0;
}

void print_control_action(pid_t pid, const char *action) {
    printf("Process %d has been %s.\n", pid, action);
}

