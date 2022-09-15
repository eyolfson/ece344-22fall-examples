CFLAGS = -std=c17 -Wpedantic -Wall -O2 -pipe -fno-plt -fPIC
ifeq ($(shell uname -s),Darwin)
	LDFLAGS =
else
	LDFLAGS = -lrt -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
endif

.PHONY: all
all: orphan-example zombie-example wait-example

orphan-example: orphan-example.o

zombie-example: zombie-example.o

wait-example: wait-example.o

.PHONY: clean
clean:
	rm -f orphan-example.o orphan-example
	rm -f zombie-example.o zombie-example
	rm -f wait-example.o wait-example
