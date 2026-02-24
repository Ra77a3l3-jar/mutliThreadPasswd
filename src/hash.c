#include "hash.h"

uint64_t hash(const char *input) {
    uint64_t hash = 1469598103934665603ULL;

    for(int i = 0; i < WORK_FACTOR; i++) {
        const char *p = input;
        while(*p) {
            hash ^= (uint64_t)(*p++);
            hash *= 1099511628211ULL;
        }
    }
    return hash;
}
