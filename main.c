#include "bits/time.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PASSWD 1000000

int main(void) {
    char passwd[] = "98427";
    char result[7];

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    long attempts = 0;

    for(int i = 0; i < MAX_PASSWD; i++) {
        sprintf(result, "%d", i);
        attempts++;

        if(strcmp(result, passwd) == 0) {
            clock_gettime(CLOCK_MONOTONIC, &end);
            double elapsed = (end.tv_sec - start.tv_sec) +
                             (end.tv_nsec - start.tv_nsec) / 1e9;
            
            printf("Password found: %s\n", result);
            printf("Attempts: %ld\n", attempts);
            printf("Time: %.6f seconds\n", elapsed);
            printf("Speed: %.2f attempts/second\n", attempts / elapsed);
            return 0;
        }        
    }
    printf("Password not found.\n");
    return 0;
}
