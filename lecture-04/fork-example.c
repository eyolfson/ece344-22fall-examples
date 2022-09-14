#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid = fork();
  if (pid > 0) {
    printf("Parent returned pid: %d\n", pid);
    printf("Parent pid: %d\n", getpid());
    printf("Parent parent pid: %d\n", getppid());
    usleep(1000);
  }
  else if (pid == 0) {
    printf("Child returned pid: %d\n", pid);
    printf("Child pid: %d\n", getpid());
    printf("Child parent pid: %d\n", getppid());
  }
  else {
    int err = errno;
    perror("fork failed");
    return err;
  }
  return 0;
}
