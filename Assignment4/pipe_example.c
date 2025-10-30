#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[BUFFER_SIZE];

    printf("Inter-Process Communication using Pipes\n");
    printf("========================================\n\n");

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process - reader
        close(pipefd[1]); // Close unused write end

        printf("Child: Waiting to read from pipe...\n");
        
        ssize_t bytes_read = read(pipefd[0], read_msg, BUFFER_SIZE);
        if (bytes_read > 0) {
            read_msg[bytes_read] = '\0';
            printf("Child: Received message: \"%s\"\n", read_msg);
        } else {
            perror("read failed");
        }

        close(pipefd[0]);
        exit(0);
    } else {
        // Parent process - writer
        close(pipefd[0]); // Close unused read end

        printf("Parent: Sending message through pipe...\n");
        
        ssize_t bytes_written = write(pipefd[1], write_msg, strlen(write_msg));
        if (bytes_written == -1) {
            perror("write failed");
            exit(1);
        }
        
        printf("Parent: Message sent (%zd bytes)\n", bytes_written);

        close(pipefd[1]);
        
        // Wait for child to complete
        wait(NULL);
        
        printf("\nParent: Communication completed successfully\n");
    }

    return 0;
}
