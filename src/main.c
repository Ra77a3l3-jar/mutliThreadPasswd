#include <stdio.h>
#include <time.h>
#include "bits/time.h"
#include "brute.h"
#include "hash.h"

int main(void) {
    char passwd[] = "457229";

    uint64_t target_hash = hash(passwd);

    int threads = 4;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    brute_force(target_hash, threads);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Total time: %.6f seconds\n", elapsed);       
}
