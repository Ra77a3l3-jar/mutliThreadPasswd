#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

// Includes: 0-9, a-z, A-Z, and common special characters
#define CHARSET "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+[]{}|;:,.<>?/"
#define CHARSET_SIZE (sizeof(CHARSET) - 1)  // 79 characters

void int_to_string(int val, char *buff, int width);
void index_to_password(uint64_t index, char *buff, int length);

#endif
