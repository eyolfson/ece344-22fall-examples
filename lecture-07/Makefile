CFLAGS = -std=gnu17 -Wpedantic -Wall -O0 -pipe -fno-plt -fPIC -pthread
ifeq ($(shell uname -s),Darwin)
	LDFLAGS = -pthread
else
	LDFLAGS = -lrt -pthread -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
endif

.PHONY: all
all: create-fork create-pthread detached-error detached-fixed stack-size

create-fork: create-fork.o

create-pthread: create-pthread.o

detached-error: detached-error.o

detached-fixed: detached-fixed.o

stack-size: stack-size.o

.PHONY: clean
clean:
	rm -f create-fork.o create-fork
	rm -f create-pthread.o create-pthread
	rm -f detached-error.o detached-error
	rm -f detached-fixed.o detached-fixed
	rm -f stack-size.o stack-size
