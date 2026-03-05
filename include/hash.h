#ifndef HASH_H
#define HASH_H

#include <stdint.h>

#ifdef __CUDACC__
#define HOST_DEVICE __host__ __device__
#else
#define HOST_DEVICE
#endif

#define WORK_FACTOR 500

HOST_DEVICE uint64_t hash(const char *input);

#endif
