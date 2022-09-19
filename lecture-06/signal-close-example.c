#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int fd = -1;

void handle_signal(int signum)
{
  printf("Closing file and exiting...\n");

  if (fd == -1) {
    printf("No open file\n");
    exit(0);
  }

  int ret = close(fd);
  if (ret == -1) {
    int err = errno;
    perror("close");
    exit(err);
  }
  printf("Closed file\n");

  sleep(10);

  exit(0);
}

void register_signal(int signum)
{
  struct sigaction new_action = {0};
  sigemptyset(&new_action.sa_mask);
  new_action.sa_handler = handle_signal;
  if (sigaction(signum, &new_action, NULL) == -1) {
    int err = errno;
    perror("sigaction");
    exit(err);
  }
}

int main(int argc, char *argv[])
{
  if (argc > 2) {
    return EINVAL;
  }

  printf("I am pid: %d\n", getpid());

  if (argc == 2) {
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
      int err = errno;
      perror("open");
      return err;
    }
    printf("Opened fd: %d\n", fd);
  }

  register_signal(SIGINT);
  register_signal(SIGTERM);

  while (true) {
    sleep(9999);
  }

  return 0;
}
