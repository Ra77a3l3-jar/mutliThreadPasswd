#include "util.h"

void int_to_string(int val, char *buff, int width) {
    for(int i = width - 1; i >= 0; i--) {
        buff[i] = '0' + (val % 10);
        val /= 10;
    }
    buff[width] = '\0';
}
