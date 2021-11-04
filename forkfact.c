#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define PIPE_BUFF 1024

int fact(int n) {
    /* Do the factorial work */
    if(n == 0) {
        return 1;
    }

    return n * fact(n - 1);
}

void childWorker(char *n, int pfd) {
    int result = fact(atoi(n));
    char buff[PIPE_BUFF];

    /* Convert the result to a string so we can write it to the pipe */
    snprintf(buff, PIPE_BUFF, "%d", result);
    write(pfd, buff, PIPE_BUFF);
}

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: ./%s <n>\n", argv[0]);
        return -1;
    }

    pid_t pid;
    int n = 0;
    int pipefd[2];

    /* No error checking for simplicity */
    n = atoi(argv[1]);
    if(n < 0) {
        fprintf(stderr, "Cannot take factorial of a negative number.\n");
        return -1;
    }

    /* Create pipe */
    if(0 > pipe(pipefd)) {
        fprintf(stderr, "Unable to create pipe\n");
        return -1;
    }

    /* Create child process */
    pid = fork();
    if(pid < 0) {
        fprintf(stderr, "Failed to create child\n");
        return -1;
    }
    else if(pid == 0) {
        /* Do factorial work in child */
        childWorker(argv[1], pipefd[1]);
    }
    else {
        /* Wait on the process to finish */
        wait(NULL);

        /* Read the data it put into the pipe, the factorial */
        char buffer[PIPE_BUFF];
        read(pipefd[0], buffer, PIPE_BUFF);
        printf("Child calculated factorial to be: %s\n", buffer);

        /* Close our pipes */
        close(pipefd[0]);
        close(pipefd[1]);
    }

 
    return 0;
}