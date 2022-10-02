#include <pthread.h>
#include <unistd.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* print_first(__attribute__((unused)) void* arg) {
    pthread_mutex_lock(&mutex);
    write(1, "This ", 5);
    write(1, "is ", 3);
    write(1, "first\n", 6);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* print_second(__attribute__((unused)) void* arg) {
    pthread_mutex_lock(&mutex);
    write(1, "I'm ", 4);
    write(1, "going ", 6);
    write(1, "second\n", 7);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(__attribute__((unused)) int argc,
         __attribute__((unused)) char *argv[]) {
    pthread_t thread[2];
    pthread_create(&thread[0], NULL, &print_first, NULL);
    pthread_create(&thread[1], NULL, &print_second, NULL);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    return 0;
}
