#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    

    if (argc <2){
        printf("There is no input from the user\n");
    }

    if (argc == 2) {
        int pipe_fd[2];
        pid_t child_pid = fork();

        if (pipe(p) < 0) exit(1); // create and check for pipe in program
        if (child_pid == -1) {
            printf("Fork failed\n");
            return 1;
        }

        else if (child_pid == 0) {
            char *endptr; // Used to check for conversion errors
            long int value = strtol(argv[1], &endptr, 10);
            int child_value = fib(value);
            printf("Child give %d\n", child_value);
            write(pipe_fd[1], &child_value, sizeof(child_value));
            close(pipe_fd[1]);
            exit(0);
        } 

        else {
            printf("start parent process\n");
            wait(NULL);
            int new_val;
            read(pipe_fd[0], &new_val, sizeof(new_val));
            close(pipe_fd[0]); // Close the read end of the pipe
            close(pipe_fd[1]); // Close the write end of the pipe
            printf("The fibbonacci number is %d\n", new_val);
            return 0;
        }
    }

    else if (argc == 3){
        printf("Too many\n");
    }
    else if (argc == 4){
        printf("Too many\n");
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