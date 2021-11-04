#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* Should NOT be modified by a signal handler */
int global = 0;

/* CAN be modified by a signal handler */
volatile sig_atomic_t atomic_global = 0;

void sighandler(int sig) {
  atomic_global = 1;
  /* This is NOT an atomic write, or reentrant, and therefore not async-signal-safe */
  // printf("SIGINT handler called!\n");

  /* write() is defined by POSIX async-signal-safe */
  write(0, "SIGINT Handler called!\n", 23);
}

int main() {
  struct sigaction sig;
  char buff[1024];

  sig.sa_handler = sighandler;
  // sig.sa_flags = 0;
  sig.sa_flags = SA_RESTART;
  sigemptyset(&sig.sa_mask);

  if(-1 == sigaction(SIGINT, &sig, NULL)) {
    fprintf(stderr, "Unable to set sigaction\n");
    return -1;
  }

  printf("Enter a string: ");
  /* fgets() uses syscalls to do its work, so interrupting it will throw
     an unrecoverable error (unless sa_flags is set)
  */
  if(fgets(buff, sizeof(buff), stdin) == NULL) {
    perror("fgets");
  }
  else {
    printf("You entered: %s\n", buff);
  }

  printf("Signal handler called? %d\n", atomic_global);

  return 0;
}
