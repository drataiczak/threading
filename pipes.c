#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MSG_SIZE 1024

int main() {
    int pipefd[2];
    char *msg = "Here's some data to pipe to your parent!";
    char buffer[MSG_SIZE];

    if(0 > pipe(pipefd)) {
        fprintf(stderr, "[!] Unable to create pipe\n");
        return -1;
    }

    if(0 == fork()) {
        /* Child code to write to pipe */
        printf("[+] Child writing to pipe\n");
        write(pipefd[1], msg, MSG_SIZE);
        printf("[+] Exiting child process\n");
    } else {
        wait(NULL);
        printf("[+] Parent reading from pipe\n");
        read(pipefd[0], buffer, MSG_SIZE);
        printf("[+] Parent read from pipe: %s\n", buffer);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    
    return 0;
}