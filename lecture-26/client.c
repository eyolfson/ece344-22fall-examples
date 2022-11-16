#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define errno_exit(str)                                                        \
  do { int err = errno; perror(str); exit(err); } while (0)

#define SOCKET_PATH "example.sock"

int main(int argc, char **argv) {
  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd == -1) {
    errno_exit("socket");
  }

  struct sockaddr_un sockaddr = {0};
  sockaddr.sun_family = AF_UNIX;
  strncpy(sockaddr.sun_path, SOCKET_PATH, sizeof(sockaddr.sun_path) - 1);

  if (connect(fd, (const struct sockaddr*) &sockaddr, sizeof(sockaddr))) {
    errno_exit("connect");
  }

  char buffer[4096];
  ssize_t bytes_read;
  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
    /* Just keep reading all the data we can */
  }
  if (bytes_read == -1) {
    errno_exit("read");
  }

  printf("Received: \"%s\"\n", buffer);

  close(fd);
  
  return 0;
}
