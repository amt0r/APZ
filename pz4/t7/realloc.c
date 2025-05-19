#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int a;
    double b;
};

int main() {
    struct sbar *ptr, *newptr;

    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        perror("calloc failed");
        return 1;
    }

    newptr = realloc(ptr, 500 * sizeof(struct sbar));
    if (!newptr) {
        perror("realloc failed");
        free(ptr);
        return 1;
    }

    ptr = newptr;

    free(ptr);
    return 0;
}
