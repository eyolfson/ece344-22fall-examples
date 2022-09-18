CFLAGS = -std=gnu17 -Wpedantic -Wall -O2 -pipe -fno-plt -fPIC
ifeq ($(shell uname -s),Darwin)
	LDFLAGS =
else
	LDFLAGS = -lrt -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
endif

.PHONY: all
all: read-write-example open-example signal-example signal-example-2

read-write-example: read-write-example.o

open-example: open-example.o

signal-example: signal-example.o

signal-example-2: signal-example-2.o

.PHONY: clean
clean:
	rm -f read-write-example.o read-write-example
	rm -f open-example.o open-example
	rm -f signal-example.o signal-example
	rm -f signal-example-2.o signal-example-2
