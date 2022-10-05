CFLAGS = -std=c17 -Wpedantic -Wall -O2 -pipe -fno-plt -fPIC
ifeq ($(shell uname -s),Darwin)
	LDFLAGS =
else
	LDFLAGS = -lrt -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
endif

.PHONY: all
all: lib-v1 lib-v1/libpoint.so lib-v2 lib-v2/libpoint.so alloc-wrapper.so alloc-example point-example

lib-v1:
	mkdir lib-v1

lib-v1/libpoint.so: libpoint-v1.o
	$(CC) $^ -shared -ldl $(LDFLAGS) -o $@

lib-v2:
	mkdir lib-v2

lib-v2/libpoint.so: libpoint-v2.o
	$(CC) $^ -shared -ldl $(LDFLAGS) -o $@

alloc-wrapper.so: alloc-wrapper.o
	$(CC) $^ -shared -ldl $(LDFLAGS) -o $@

alloc-example: alloc-example.o

point-example: point-example.o
	$(CC) $< -Llib-v1 -lpoint $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -f alloc-wrapper.o alloc-wrapper.so
	rm -f alloc-example.o alloc-example
	rm -f point-example.o point-example
	rm -rf lib-v1
	rm -f libpoint-v1.o
	rm -rf lib-v2
	rm -f libpoint-v2.o
