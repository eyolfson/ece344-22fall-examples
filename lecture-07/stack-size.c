#include <pthread.h>
#include <stdio.h>

int main()
{
  size_t stacksize;
  pthread_attr_t attributes;
  pthread_attr_init(&attributes);
  pthread_attr_getstacksize(&attributes, &stacksize);
  printf("Stack size = %li\n", stacksize);
  pthread_attr_destroy(&attributes);
  return 0;
}
