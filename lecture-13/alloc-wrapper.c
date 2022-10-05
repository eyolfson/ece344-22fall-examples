#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

void *malloc(size_t size)
{
  void* (*malloc_ptr)(size_t);
  *(void**) (&malloc_ptr) = dlsym(RTLD_NEXT, "malloc");
  void *ret = (*malloc_ptr)(size);

  char buf[200];
  int buf_size = sprintf(buf, "Call to malloc(%lu) = %p\n", size, ret);
  write(1, buf, buf_size);

  return ret;
}

void *realloc(void *ptr, size_t size)
{
  void* (*realloc_ptr)(void *, size_t);
  *(void**) (&realloc_ptr) = dlsym(RTLD_NEXT, "realloc");
  void *ret = (*realloc_ptr)(ptr, size);

  char buf[200];
  int buf_size = sprintf(buf, "Call to realloc(%p, %lu) = %p\n", ptr, size, ret);
  write(1, buf, buf_size);

  return ret;
}

void *calloc(size_t nmemb, size_t size)
{
  void* (*calloc_ptr)(size_t, size_t);
  *(void**) (&calloc_ptr) = dlsym(RTLD_NEXT, "calloc");
  void *ret = (*calloc_ptr)(nmemb, size);

  char buf[200];
  int buf_size = sprintf(buf, "Call to calloc(%lu, %lu) = %p\n", nmemb, size, ret);
  write(1, buf, buf_size);

  return ret;
}

void free(void *ptr)
{
  void (*free_ptr)(void *);
  *(void**) (&free_ptr) = dlsym(RTLD_NEXT, "free");
  (*free_ptr)(ptr);

  char buf[200];
  int buf_size = sprintf(buf, "Call to free(%p)\n", ptr);
  write(1, buf, buf_size);
}
