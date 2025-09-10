#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_fcfs() {
    int n;
    printf("\n[FCFS Scheduling]\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    pid_t pids[n];

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child: simulate work
            printf("Process P%d (PID=%d) started\n", i + 1, getpid());
            for (int j = 0; j < 5; j++) {
                printf("P%d (PID=%d) working... %d\n", i + 1, getpid(), j + 1);
                sleep(1);
            }
            printf("Process P%d (PID=%d) finished\n", i + 1, getpid());
            exit(0);
        } else {
            pids[i] = pid;
            // Parent waits one by one (FCFS order)
            waitpid(pid, NULL, 0);
        }
    }
}