#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    pid_t pid1, pid2;
    int status;

    // Seed the random number generator
    srandom(time(NULL));

    // Create the first child process
    if ((pid1 = fork()) == 0) {
        // Child Process 1
        int iterations = random() % 30 + 1; // Random number of iterations between 1 and 30
        for (int i = 0; i < iterations; i++) {
            printf("Child Pid: %d is going to sleep!\n", getpid());
            sleep(random() % 11); // Sleep for a random time between 0 and 10 seconds
            printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
        }
        exit(0); // Terminate the child process
    }

    // Create the second child process
    if ((pid2 = fork()) == 0) {
        // Child Process 2
        int iterations = random() % 30 + 1; // Random number of iterations between 1 and 30
        for (int i = 0; i < iterations; i++) {
            printf("Child Pid: %d is going to sleep!\n", getpid());
            sleep(random() % 11); // Sleep for a random time between 0 and 10 seconds
            printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
        }
        exit(0); // Terminate the child process
    }

    // Parent Process
    while ((pid1 = wait(&status)) > 0) { // Wait for child processes to complete
        printf("Child Pid: %d has completed\n", pid1);
    }

    return 0;
}
