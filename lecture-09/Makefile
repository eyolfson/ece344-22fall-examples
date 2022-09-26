CFLAGS = -std=gnu17 -Wpedantic -Wall -O0 -pipe -fno-plt -fPIC -pthread
ifeq ($(shell uname -s),Darwin)
	LDFLAGS = -pthread
else
	LDFLAGS = -lrt -pthread -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
endif

.PHONY: all
all: pthread-datarace-fixed

pthread-datarace-fixed: pthread-datarace-fixed.o

.PHONY: clean
clean:
	rm -f pthread-datarace-fixed.o pthread-datarace-fixed
