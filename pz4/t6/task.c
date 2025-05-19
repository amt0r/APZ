#include <stdio.h>
#include <stdlib.h>

int main() {
    void *p1 = realloc(NULL, 100);
    if (p1 == NULL) {
        printf("realloc(NULL, 100) failed\n");
    } else {
        printf("realloc(NULL, 100) succeeded: %p\n", p1);
    }

    void *p2 = realloc(p1, 0);
    if (p2 == NULL) {
        printf("realloc(p1, 0) returned NULL\n");
    } else {
        printf("realloc(p1, 0) returned pointer: %p\n", p2);
    }

    if (p2 != NULL)
        free(p2);

    return 0;
}
