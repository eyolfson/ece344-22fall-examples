#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_BALANCE 1000
#define NUM_TRANSFERS 500000001
#define TRANSFER_AMOUNT 100
#define NUM_THREADS 8

struct account {
    uint64_t id;
    uint64_t balance;
};

static uint64_t num_accounts = 0;
static struct account* accounts = NULL;

static void transfer(struct account* from, struct account* to, uint64_t amount) {
    if (from->balance < amount) {
        return;
    }
    from->balance -= amount;
    to->balance += amount;
}

void* run(void* arg) {
    uint32_t thread_id = *((uint32_t *) arg);
    free(arg);

    /* Calculate the number of transfers per thread
       (handle if the global number of transfers isn't divisible) */
    uint64_t num_transfers = NUM_TRANSFERS / NUM_THREADS;
    if ((NUM_TRANSFERS % NUM_THREADS) > thread_id) {
        ++num_transfers;
    }

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
    assert(num_accounts != 0 && num_accounts != ULONG_MAX);
    assert(errno == 0);

    size_t accounts_size = num_accounts * sizeof(struct account);
    accounts = malloc(accounts_size);
    assert(accounts != NULL);

    for (uint64_t i = 0; i < num_accounts; ++i) {
        accounts[i].id = i + 1;
        accounts[i].balance = STARTING_BALANCE;
    }
    printf("Bank initial funds: $%'lu\n", STARTING_BALANCE * num_accounts);

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
        uint64_t from_index = random() % num_accounts;
        uint64_t to_index = random() % num_accounts;
        transfer(&accounts[from_index], &accounts[to_index], TRANSFER_AMOUNT);
    }

    uint64_t total_balance = 0;
    for (uint64_t i = 0; i < num_accounts; ++i) {
        total_balance += accounts[i].balance;
    }

    printf("Bank final funds:   $%'lu\n", total_balance);

    free(accounts);

    return 0;
}