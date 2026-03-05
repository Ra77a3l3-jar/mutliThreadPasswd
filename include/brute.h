#ifndef BRUTE_H
#define BRUTE_H

#include <stdint.h>

#ifdef __CUDACC__
#define GLB __global__
#else
#define GLB
#endif

GLB void bruteForceKernel(uint64_t target_hash, uint64_t max, int length, char *found_password);

#endif
