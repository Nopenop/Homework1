#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // This code runs in the child process
        printf("Child process, PID: %d\n", getpid());
    } else {
        // This code runs in the parent process
        printf("Parent process, Child PID: %d\n", child_pid);
    }

    return 0;
}