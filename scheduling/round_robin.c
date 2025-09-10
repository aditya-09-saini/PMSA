#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

struct RRJob {
    int pid;
    int burst;
    int remaining;
    pid_t real_pid;
};

void run_round_robin() {
    int n, tq;
    printf("\n[Round Robin Scheduling]\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct RRJob jobs[n];
    for (int i = 0; i < n; i++) {
        jobs[i].pid = i + 1;
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &jobs[i].burst);
        jobs[i].remaining = jobs[i].burst;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    // Fork all processes
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child: just loop forever, parent will control execution
            while (1) pause();
        } else {
            jobs[i].real_pid = pid;
            kill(pid, SIGSTOP); // stop immediately until scheduled
        }
    }

    int remaining = n;
    while (remaining > 0) {
        for (int i = 0; i < n; i++) {
            if (jobs[i].remaining > 0) {
                kill(jobs[i].real_pid, SIGCONT);
                int slice = (jobs[i].remaining < tq) ? jobs[i].remaining : tq;
                printf("Running P%d (PID=%d) for %d sec\n", jobs[i].pid, jobs[i].real_pid, slice);
                sleep(slice);
                jobs[i].remaining -= slice;
                kill(jobs[i].real_pid, SIGSTOP);

                if (jobs[i].remaining == 0) {
                    kill(jobs[i].real_pid, SIGKILL);
                    waitpid(jobs[i].real_pid, NULL, 0);
                    printf("P%d finished\n", jobs[i].pid);
                    remaining--;
                }
            }
        }
    }
}
