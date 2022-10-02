#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* print_first(__attribute__((unused)) void* arg) {
    printf("This is first\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* print_second(__attribute__((unused)) void* arg) {
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    printf("I'm going second\n");
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
