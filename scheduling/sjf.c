#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

struct Job {
    int pid;
    int burst;
    pid_t real_pid;
};

void run_sjf() {
    int n;
    printf("\n[SJF Scheduling]\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Job jobs[n];
    for (int i = 0; i < n; i++) {
        jobs[i].pid = i + 1;
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &jobs[i].burst);
    }

    // Sort by burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (jobs[i].burst > jobs[j].burst) {
                struct Job temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Process P%d (PID=%d) started (BT=%d)\n", jobs[i].pid, getpid(), jobs[i].burst);
            for (int j = 0; j < jobs[i].burst; j++) {
                printf("P%d working... %d\n", jobs[i].pid, j + 1);
                sleep(1);
            }
            printf("Process P%d (PID=%d) finished\n", jobs[i].pid, getpid());
            exit(0);
        } else {
            jobs[i].real_pid = pid;
            waitpid(pid, NULL, 0);
        }
    }
}
