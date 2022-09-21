#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NFORKS 50000

int main(int argc, char *argv[]) {
  for (int i=0; i < NFORKS; ++i) {
    pid_t pid = fork();

    /* error checking */
    if (pid == -1) {
      int err = errno;
      perror("fork failed");
      exit(err);
    }
    /* child */
    else if (pid == 0) {
      exit(0);
    }
    /* parent */
    else {
      int wstatus;
      waitpid(pid, &wstatus, 0);
    }
  }
}
