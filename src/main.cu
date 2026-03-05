#include <cuda_runtime.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "brute.h"
#include "hash.h"
#include "util.h"

#define THREADS 1024

int main(void) {
    char target[] = "ha73d";
    uint64_t length = strlen(target);

    uint64_t target_hash = hash(target);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    uint64_t max = 1;
    for (uint64_t i = 0; i < length; i++) {
        max *= CHARSET_SIZE;
    }

    char *d_found_password;
    cudaMalloc(&d_found_password, 32 * sizeof(char));
    cudaMemset(d_found_password, 0, 32 * sizeof(char)); // Initialize with 0

    uint64_t blocks = (max + THREADS - 1) / THREADS;
    bruteForceKernel<<<blocks, THREADS>>>(target_hash, max, length, d_found_password);
    
    cudaError_t err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        printf("CUDA error: %s\n", cudaGetErrorString(err));
        cudaFree(d_found_password);
        return 1;
    }

    char found_password[32];
    cudaMemcpy(found_password, d_found_password, 32 * sizeof(char), cudaMemcpyDeviceToHost);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    if (found_password[0] != '\0') {
        printf("Password found: %s\n", found_password);
    } else {
        printf("Password not found.\n");
    }

    printf("Total time: %.6f seconds\n", elapsed);       

    cudaFree(d_found_password);
    return 0;
}
