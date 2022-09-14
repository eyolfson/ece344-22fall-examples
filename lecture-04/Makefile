CFLAGS = -std=c17 -Wpedantic -Wall -O2 -pipe -fno-plt -fPIC
ifeq ($(shell uname -s),Darwin)
	LDFLAGS =
else
	LDFLAGS = -lrt -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
endif

.PHONY: all
all: fork-example

fork-example: fork-example.o

.PHONY: clean
clean:
	rm -f fork-example.o fork-example
