#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int new_process(int id) {
    pid_t pid = fork();
    if (pid > 0) {
        return 0;
    }
    else if (pid == -1) {
        int err = errno;
        perror("fork failed");
        return err;
    }

    for (int i = 0; i < 10; ++i) {
        printf("Process %d: %d\n", id, i);
        usleep(1000);
    }
    exit(0);
}

int main(int argc, char *argv[]) {
  for (int i = 1; i <= 4; ++i) {
    int err = new_process(i);
    if (err != 0) {
        return err;
    }
  }
  return 0;
}
