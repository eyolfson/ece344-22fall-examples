#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void * run(void * arg) {
    int id = *((int *) arg);
    free(arg);
    for (int i = 0; i < 10; ++i) {
        printf("Thread %d: %d\n", id, i);
        usleep(1000);
    }
    return NULL;
}

int new_thread(int id) {
    int * arg = (int *) malloc(sizeof(int));
    *arg = id;
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, run, arg);
    return rc;
}

int main(int argc, char *argv[]) {
  for (int i = 1; i <= 4; ++i) {
    int err = new_thread(i);
    if (err != 0) {
        return err;
    }
  }
  pthread_exit(0);
  return 0;
}
