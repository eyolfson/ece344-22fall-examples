#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

static sem_t sem;

void* print_first(__attribute__((unused)) void* arg) {
    printf("This is first\n");
    sem_post(&sem);
    return NULL;
}

void* print_second(__attribute__((unused)) void* arg) {
    sem_wait(&sem);
    printf("I'm going second\n");
    return NULL;
}

int main(__attribute__((unused)) int argc,
         __attribute__((unused)) char *argv[]) {
    sem_init(&sem, 0, 0);

    pthread_t thread[2];
    pthread_create(&thread[0], NULL, &print_first, NULL);
    pthread_create(&thread[1], NULL, &print_second, NULL);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    return 0;
}
