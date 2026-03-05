#include "util.h"

HOST_DEVICE void index_to_password(uint64_t index, char *buff, int length) {
    // Convert index to password using base-CHARSET_SIZE number system
    for(int i = length - 1; i >= 0; i--) {
        buff[i] = CHARSET[index % CHARSET_SIZE];
        index /= CHARSET_SIZE;
    }
    buff[length] = '\0';
}
