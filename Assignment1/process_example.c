#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    printf("Parent process starting (PID: %d)\n", getpid());

    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        printf("Child process exiting\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent process created child with PID: %d\n", pid);
        printf("Parent waiting for child to complete...\n");
        
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
        
        printf("Parent process exiting\n");
    }

    return 0;
}
