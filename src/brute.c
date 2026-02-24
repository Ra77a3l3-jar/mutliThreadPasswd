#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <string.h>
#include "brute.h"
#include "hash.h"
#include "util.h"

typedef struct {
    int start;
    int end;
    uint64_t target_hash;
    uint64_t lenght;
} thread_data_t;

atomic_int found = 0; // atomic allows safe access with concurrency

void *worker(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char guess[32];

    for(int i = data->start; i < data->end && !atomic_load_explicit(&found, memory_order_relaxed); i++) { // atomic_load retrives safelly value
        int_to_string(i, guess, data->lenght);

        if(hash(guess) == data->target_hash) {
            printf("Passowrd found: %s\n", guess);
            atomic_store_explicit(&found, 1, memory_order_relaxed);
            break;
        }
    }
    return NULL;
}

void brute_force(uint64_t target_hash, int threads, uint64_t lenght) {
    atomic_store(&found, 0);

    long max = 1;
    for(uint64_t i = 0; i < lenght; i++) {
        max *= 10;
    } // calculates max number of options for given lenght (might overflow uint64)

    pthread_t *thread = malloc(sizeof(pthread_t) * threads);
    thread_data_t *thread_data = malloc(sizeof(thread_data_t) * threads);

    int chunk = max / threads;

    for(int i = 0; i < threads; i++) {
        thread_data[i].start = i * chunk;
        thread_data[i].end = (i == threads - 1) ? max : (i + 1) * chunk;
        thread_data[i].target_hash = target_hash;
        thread_data[i].lenght = lenght;

        pthread_create(&thread[i], NULL, worker, &thread_data[i]);
        /* create thread by thread with its pointer to data
        and the function that will be run*/
    }

    for(int i = 0; i < threads; i++) {
        pthread_join(thread[i], NULL); // makes the thread wait for the other to finish
    }

    free(thread);
    free(thread_data);
}
