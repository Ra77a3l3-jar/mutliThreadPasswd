#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define MAX_PASSWD 1000000
#define WORK_FACTOR 500

// Mock hash
uint64_t hash(const char *input) {
    uint64_t hash = 1269598103934665603ULL;

    for(int i = 0; i < WORK_FACTOR; i++) {
        const char *p = input;
        while(*p) {
            hash ^= (uint64_t)(*p++);
            hash *= 1099511628211ULL; 
        }
    }
    return hash;
}

int main(void) {
    char passwd[] = "98427";
    char guess[7];

    uint64_t target_hash = hash(passwd);

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    long attempts = 0;

    for(int i = 0; i < MAX_PASSWD; i++) {
        sprintf(guess, "%d", i);
        attempts++;

        if(hash(guess) == target_hash) {
            clock_gettime(CLOCK_MONOTONIC, &end);
            double elapsed = (end.tv_sec - start.tv_sec) +
                             (end.tv_nsec - start.tv_nsec) / 1e9;
            
            printf("Password found: %s\n", guess);
            printf("Attempts: %ld\n", attempts);
            printf("Time: %.6f seconds\n", elapsed);
            printf("Speed: %.2f attempts/second\n", attempts / elapsed);
            return 0;
        }        
    }
    printf("Password not found.\n");
    return 0;
}
