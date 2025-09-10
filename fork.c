#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void fork_demo() {
    printf("\n[Fork Demo]\n");

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
    } else if (pid == 0) {
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());
    } else {
        wait(NULL);
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);
    }
}
