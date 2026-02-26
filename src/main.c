#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "bits/time.h"
#include "brute.h"
#include "hash.h"

int main(void) {
    char passwd[] = "az9g";
    uint64_t lenght = 4;
    int threads = 8;

    uint64_t target_hash = hash(passwd);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    brute_force(target_hash, threads, lenght);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Total time: %.6f seconds\n", elapsed);       
}
