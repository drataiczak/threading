#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  pid_t pid;
  int ret;
  int status;

  pid = fork();
  if(pid < 0) {
    fprintf(stderr, "[!] Unable to fork()\n");
    return -1;
  }
  else if(pid == 0) {
    /* Arg list must end with NULL */
    char *argv[] = { "forkfact.out", "5", NULL };
    printf("[%d] Building command line for execv\n", getpid());

    if(-1 == execv("/home/devin/Documents/threading/forkfact", argv)) {
      fprintf(stderr, "[!] Error calling execv()\n");
      exit(-1);
    }

    exit(0);
  }
  else {
    wait(&status);
    printf("Child process exited with %d\n", WEXITSTATUS(status));
  }

  return 0;
}
