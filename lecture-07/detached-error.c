#include <pthread.h>
#include <stdio.h>

void* run(void* ptr) {
  printf("In run\n");
  return NULL;
}

int main() {
  pthread_t thread;
  pthread_create(&thread, NULL, &run, NULL);
  pthread_detach(thread);
  printf("In main\n");
  return 0;
}
