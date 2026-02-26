#include "util.h"

void int_to_string(int val, char *buff, int width) {
    for(int i = width - 1; i >= 0; i--) {
        buff[i] = '0' + (val % 10);
        val /= 10;
    }
    buff[width] = '\0';
}

void index_to_password(uint64_t index, char *buff, int length) {
    // Convert index to password using base-CHARSET_SIZE number system
    for(int i = length - 1; i >= 0; i--) {
        buff[i] = CHARSET[index % CHARSET_SIZE];
        index /= CHARSET_SIZE;
    }
    buff[length] = '\0';
}
