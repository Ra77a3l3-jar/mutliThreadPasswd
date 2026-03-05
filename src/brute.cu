#include <stdint.h>
#include <stdlib.h>
#include "brute.h"
#include "hash.h"
#include "util.h"

GLB void bruteForceKernel(uint64_t target_hash, uint64_t max, int length, char *found_password) {
    uint64_t idx = blockIdx.x * blockDim.x + threadIdx.x;
    char guess[32];

    if (idx < max) {
        index_to_password(idx, guess, length);
        if (hash(guess) == target_hash) {
            // Copy result to global memory
            for (int i = 0; i < length; i++) {
                found_password[i] = guess[i];
            }
            found_password[length] = '\0';
        }
    }
}

