#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 8

static int counter = 0;

void* run(void* arg)
{
    int i;
    for (i = 0; i < 10000; ++i) {
        ++counter;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&thread[i], NULL, &run, NULL);
    }

    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thread[i], NULL);
    }

    printf("counter = %i\n", counter);
    return 0;
}
