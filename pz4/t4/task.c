#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void *ptr = NULL;
    int i = 0;

    while (i++ < 3) {
        if (!ptr)
            ptr = malloc(16);

        strcpy(ptr, "Test");

        printf("Iteration %d: %s\n", i, (char*)ptr);

        free(ptr);
        // ptr = NULL
    }

    return 0;
}
