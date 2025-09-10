#include <stdio.h>
#include <stdlib.h>

// external functions from other files
extern void fork_demo();
extern void run_fcfs();
extern void run_sjf();
extern void run_priority();
extern void run_round_robin();
extern void process_monitor();
extern void process_actions();

void menu() {
    printf("\n=== Process Management & Scheduling Project ===\n");
    printf("1. Demonstrate fork() and wait()\n");
    printf("2. First Come First Serve (FCFS)\n");
    printf("3. Shortest Job First (SJF)\n");
    printf("4. Priority Scheduling\n");
    printf("5. Round Robin Scheduling\n");
    printf("6. Process Monitor\n");
    printf("7. Kill/Suspend/Resume Process\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main() {
    int choice;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: fork_demo(); break;
            case 2: run_fcfs(); break;
            case 3: run_sjf(); break;
            case 4: run_priority(); break;
            case 5: run_round_robin(); break;
            case 6: process_monitor(); break;
            case 7: process_actions(); break;
            case 0: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
