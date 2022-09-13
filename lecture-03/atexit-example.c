#include <stdio.h>
#include <stdlib.h>

void fini(void)
{
  puts("Do fini");
}

int main(int argc, char **argv)
{
  atexit(fini);
  puts("Do main");
  return 0;
}
