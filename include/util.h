#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#ifdef __CUDACC__
#define HOST_DEVICE __host__ __device__
#else
#define HOST_DEVICE
#endif

// Includes: 0-9, a-z, A-Z, and common special characters
#define CHARSET "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+[]{}|;:,.<>?/"
#define CHARSET_SIZE (sizeof(CHARSET) - 1)  // 79 characters

HOST_DEVICE void index_to_password(uint64_t index, char *buff, int length);

#endif
