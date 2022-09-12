CFLAGS = -std=c17 -Wpedantic -Wall -O2 -pipe -fno-plt
ifeq ($(shell uname -s),Darwin)
	LDFLAGS =
else
	LDFLAGS = -lrt -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
endif

.PHONY: all
all: execve-example

execve-example: execve-example.o

.PHONY: clean
clean:
	rm -f execve-example.o execve-example
