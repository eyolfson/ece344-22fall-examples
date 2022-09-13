CFLAGS = -std=c17 -Wpedantic -Wall -O2 -pipe -fno-plt
ifeq ($(shell uname -s),Darwin)
	LDFLAGS =
else
	LDFLAGS = -lrt -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
endif

.PHONY: all
all: atexit-example execve-example

atexit-example: atexit-example.o

execve-example: execve-example.o

.PHONY: clean
clean:
	rm -f atexit-example.o atexit-example execve-example.o execve-example
