#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STARTING_BALANCE 1000
#define NUM_TRANSFERS 10000000
#define NUM_THREADS 8

struct account {
    uint32_t id;
    uint64_t balance;
};

static uint32_t num_accounts = 0;
static struct account* accounts = NULL;

static void securely_connect_to_bank() {
    const int64_t nsec_per_sec = 1000000000;

    /* Calculate the target time to wait until base on the current time */
    struct timespec target;
    clock_gettime(CLOCK_MONOTONIC, &target);
    target.tv_nsec += 1000;
    if (target.tv_nsec >= nsec_per_sec) {
        target.tv_nsec -= nsec_per_sec;
        target.tv_sec += 1;
    }

    /* Busy loop that keeps on reading the time */
    struct timespec current;
    while (1) {
        clock_gettime(CLOCK_MONOTONIC, &current);
        if (current.tv_sec > target.tv_sec) {
            break;
        }
        else if (current.tv_nsec >= target.tv_nsec) {
            break;
        }
    }
}

static void transfer(struct account* from, struct account* to) {
    securely_connect_to_bank();
    uint64_t amount = from->balance / 10;
    from->balance -= amount;
    to->balance += amount;
}

static void* run(void* arg) {
    uint32_t thread_id = *((uint32_t *) arg);
    free(arg);

    return NULL;
}

void check_error(int ret, const char* message) {
    if (ret == 0) {
        return;
    }
    errno = ret;
    perror(message);
    exit(ret);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return EINVAL;
    }

    setlocale(LC_NUMERIC, "");

    /* Get the number of accounts to simulate */
    errno = 0;
    num_accounts = strtoul(argv[1], NULL, 10);
    assert(num_accounts != 0);
    assert(errno == 0);

    size_t accounts_size = num_accounts * sizeof(struct account);
    accounts = malloc(accounts_size);
    assert(accounts != NULL);

    for (uint64_t i = 0; i < num_accounts; ++i) {
        accounts[i].id = i + 1;
        accounts[i].balance = STARTING_BALANCE;
    }
    printf("Bank initial funds: $%'lu\n", (uint64_t) STARTING_BALANCE * num_accounts);

    /*
    pthread_t threads[NUM_THREADS];
    for (uint32_t i = 0; i < NUM_THREADS; ++ i) {
        int* thread_id = malloc(sizeof(uint32_t));
        assert(thread_id != NULL);
        *thread_id = i;
        check_error(pthread_create(&threads[i], NULL, run, thread_id), "pthread_create");
    }

    for (uint32_t i = 0; i < NUM_THREADS; ++ i) {
        check_error(pthread_join(threads[i], NULL), "pthread_join");
    }
    */

    /* Parallelize this for loop */
    for (uint64_t i = 0; i < NUM_TRANSFERS; ++i) {
        uint64_t from_index = rand() % num_accounts;
        uint64_t to_index = rand() % num_accounts;
        transfer(&accounts[from_index], &accounts[to_index]);
    }

    uint64_t total_balance = 0;
    for (uint64_t i = 0; i < num_accounts; ++i) {
        total_balance += accounts[i].balance;
    }

    printf("Bank final funds:   $%'lu\n", total_balance);

    free(accounts);

    return 0;
}