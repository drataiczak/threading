#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid;
  int ret = -2;

  switch(pid = fork()) {
    case -1:
        fprintf(stderr, "[!] Failed to fork\n");
        ret = -1;
      break;
    case 0:
        printf("[CHILD] Child process begin execution\n");
        printf("[CHILD] Parent PID: %d\n", getppid());
        printf("[CHILD] Child PID: %d\n", getpid());
        exit(0);
      break;
    default:
        printf("[PARENT] Parent process execution\n");
        printf("[PARENT] Parent PID: %d\n", getpid());
        printf("[PARENT] Child PID: %d\n", pid);
        printf("[PARENT] Begin waiting on child\n");
        wait(&ret);
        printf("[PARENT] Child returned %d\n", WEXITSTATUS(ret));
      break;
  }


  return ret;
}
