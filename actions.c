#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void process_actions() {
    int choice, pid;

    printf("\n[Process Actions]\n");
    printf("1. Kill a process\n");
    printf("2. Suspend a process\n");
    printf("3. Resume a process\n");
    printf("Choice: ");
    scanf("%d", &choice);

    printf("Enter PID: ");
    scanf("%d", &pid);

    int result;
    switch (choice) {
        case 1:
            result = kill(pid, SIGKILL);
            if (result == 0) printf("Process %d killed.\n", pid);
            else perror("kill");
            break;
        case 2:
            result = kill(pid, SIGSTOP);
            if (result == 0) printf("Process %d suspended.\n", pid);
            else perror("suspend");
            break;
        case 3:
            result = kill(pid, SIGCONT);
            if (result == 0) printf("Process %d resumed.\n", pid);
            else perror("resume");
            break;
        default:
            printf("Invalid choice.\n");
    }
}
