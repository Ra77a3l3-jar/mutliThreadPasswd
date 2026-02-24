#include <stdio.h>
#include <string.h>

#define MAX_PASSWD 1000000

int main(void) {
    char passwd[] = "98427";
    char result[7];

    for(int i = 0; i < MAX_PASSWD; i++) {
        sprintf(result, "%d", i);

        if(strcmp(result, passwd) == 0) {
            printf("Password found: %s\n", result);
            return 0;
        }        
    }
    printf("Password not found.\n");
    return 0;
}
