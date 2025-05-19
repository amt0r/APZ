#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 100000;
    int xb = -100000;

    int num = xa * xb;
    printf("num (signed int): %d\n", num);

    void *ptr = malloc(num);

    if (ptr == NULL) {
        perror("malloc failed");
    } else {
        printf("malloc succeeded for %d bytes\n", num);
        free(ptr);
    }

    return 0;
}
