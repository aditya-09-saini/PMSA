#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

struct PJob {
    int pid;
    int burst;
    int priority;
    pid_t real_pid;
};

void run_priority() {
    int n;
    printf("\n[Priority Scheduling]\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct PJob jobs[n];
    for (int i = 0; i < n; i++) {
        jobs[i].pid = i + 1;
        printf("Enter burst time and priority for P%d: ", i + 1);
        scanf("%d %d", &jobs[i].burst, &jobs[i].priority);
    }

    // Sort by priority (descending)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (jobs[i].priority < jobs[j].priority) {
                struct PJob temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Process P%d (PID=%d, Pri=%d) started\n", jobs[i].pid, getpid(), jobs[i].priority);
            for (int j = 0; j < jobs[i].burst; j++) {
                printf("P%d working... %d\n", jobs[i].pid, j + 1);
                sleep(1);
            }
            printf("Process P%d finished\n", jobs[i].pid);
            exit(0);
        } else {
            jobs[i].real_pid = pid;
            waitpid(pid, NULL, 0);
        }
    }
}
