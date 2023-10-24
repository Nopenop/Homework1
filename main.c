#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    

    if (argc <2){
        printf("There is no input from the user");
    }

    if (argc == 2) {
        int pipe_fd[2];
        pid_t child_pid = fork();

        if (child_pid == -1) {
            printf("Fork failed");
            return 1;
        }

        else if (child_pid == 0) {
            close(pipe_fd[0]);
            char *endptr; // Used to check for conversion errors
            long int value = strtol(argv[1], &endptr, 10);
            int child_value = fib(value);
            write(pipe_fd[1], &child_value, sizeof(child_value));
            close(pipe_fd[1]);
        } 

        else {
            close(pipe_fd[1]);
            int child_value;
            read(pipe_fd[0], &child_value, sizeof(child_value));
            close(pipe_fd[0]); // Close the read end of the pipe
            printf("The fibbonacci number is %d", child_value);
        }
    }

    else if (argc == 3){
        printf("Too many");
    }
    else if (argc == 4){
        printf("Too many");
    }

    return 0;
}

int fib(long int n) {

    int a = 0, b = 1;
    int result = 0;
    if (n == 0) return a;
    int i = 2; 
    while(i <= n) {
        result = a + b;
        a = b;
        b = result;
        i++;
    }
    return b;
}