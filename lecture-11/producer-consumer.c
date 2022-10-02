#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void empty_slot();
void fill_slot();

static sem_t producer_remaining_sem;
static sem_t consumer_remaining_sem;

static uint32_t producer_ms = 100;
static uint32_t consumer_ms = 120;

static uint32_t buffer_size = 10;

void initialize_semaphores() {

}

void* producer(__attribute__((unused)) void* arg) {
    while (sem_trywait(&producer_remaining_sem) == 0) {
        usleep(producer_ms * 1000); /* simulate doing some work */
        fill_slot();
    }
    return NULL;
}

void* consumer(__attribute__((unused)) void* arg) {
    while (sem_trywait(&consumer_remaining_sem) == 0) {
        empty_slot();
        usleep(consumer_ms * 1000); /* simulate doing some work */
    }
    return NULL;
}

enum slot {
    SLOT_EMPTY,
    SLOT_FILLED,
};

static enum slot* buffer;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static uint32_t producer_index = 0;
static uint32_t consumer_index = 0;

void fill_slot() {
    pthread_mutex_lock(&mutex);
    printf("Filling slot %u\n", producer_index);
    if (buffer[producer_index] == SLOT_FILLED) {
        printf("  \033[31mSlot is already filled!\033[0m\n");
    }
    buffer[producer_index] = SLOT_FILLED;
    ++producer_index;
    if (producer_index == buffer_size) {
        producer_index = 0;
    }
    pthread_mutex_unlock(&mutex);
}

void empty_slot() {
    pthread_mutex_lock(&mutex);
    printf("Emptying slot %u\n", consumer_index);
    if (buffer[consumer_index] == SLOT_EMPTY) {
        printf("  \033[31mSlot is already empty!\033[0m\n");
    }
    buffer[consumer_index] = SLOT_EMPTY;
    ++consumer_index;
    if (consumer_index == buffer_size) {
        consumer_index = 0;
    }
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) {
    uint32_t num_to_produce = 15;

    if (argc < 3 || argc >= 8) {
        fprintf(stderr,
                "%s <num_producers> <num_consumers> <num_to_produce=%u> <buffer_size=%u> <producer_ms=%u> <consumer_ms=%u>\n",
                argv[0], num_to_produce, buffer_size, producer_ms, consumer_ms);
        return EINVAL;
    }

    /* Initialize the producer threads */
    uint32_t num_producers = atoi(argv[1]);
    if (num_producers <= 0) {
        fprintf(stderr, "Number of producers needs to be greater than 0\n");
        return EINVAL;
    }
    pthread_t* producer_threads = malloc(num_producers * sizeof(pthread_t));

    /* Initialize the consumer threads */
    uint32_t num_consumers = atoi(argv[2]);
    if (num_consumers <= 0) {
        fprintf(stderr, "Number of consumers needs to be greater than 0\n");
        return EINVAL;
    }
    pthread_t* consumer_threads = malloc(num_consumers * sizeof(pthread_t));

    /* Initialize semaphores used to bound the number of calls to fill and empty slots */
    if (argc >= 4) {
        num_to_produce = atoi(argv[3]);
        if (num_to_produce <= 0) {
            fprintf(stderr, "Number to produce needs to be greater than 0\n");
            return EINVAL;
        }
    }
    sem_init(&producer_remaining_sem, 0, num_to_produce);
    sem_init(&consumer_remaining_sem, 0, num_to_produce);

    /* Initialize the buffer */
    if (argc >= 5) {
        buffer_size = atoi(argv[4]);
        if (buffer_size <= 0) {
            fprintf(stderr, "Buffer size needs to be greater than 0\n");
            return EINVAL;
        }
    }
    buffer = malloc(buffer_size * sizeof(enum slot));
    for (uint32_t i = 0; i < buffer_size; ++i) {
        buffer[0] = SLOT_EMPTY;
    }

    /* Set the producer time (in milliseconds) */
    if (argc >= 6) {
        producer_ms = atoi(argv[5]);
        if (producer_ms <= 0 || producer_ms > 1000) {
            fprintf(stderr, "Producer time (in milliseconds) needs to be between 1 and 1000\n");
            return EINVAL;
        }
    }

    /* Set the consumer time (in milliseconds) */
    if (argc >= 7) {
        consumer_ms = atoi(argv[6]);
        if (consumer_ms <= 0 || consumer_ms > 1000) {
            fprintf(stderr, "Consumer time (in milliseconds) needs to be between 1 and 1000\n");
            return EINVAL;
        }
    }

    /* Initialize semaphores used to ensure we don't overrun the buffer */
    initialize_semaphores();

    /* Create the producer threads */
    for (uint32_t i = 0; i < num_producers; ++i) {
        pthread_create(&producer_threads[i], NULL, &producer, NULL);
    }

    /* Create the consumer threads */
    for (uint32_t i = 0; i < num_consumers; ++i) {
        pthread_create(&consumer_threads[i], NULL, &consumer, NULL);
    }

    /* Join the producer threads */
    for (uint32_t i = 0; i < num_producers; ++i) {
        pthread_join(producer_threads[i], NULL);
    }

    /* Join the consumer threads */
    for (uint32_t i = 0; i < num_consumers; ++i) {
        pthread_join(consumer_threads[i], NULL);
    }

    /* Clean up all our resources */
    sem_destroy(&producer_remaining_sem);
    sem_destroy(&consumer_remaining_sem);
    free(consumer_threads);
    free(producer_threads);
    free(buffer);

    return 0;
}

