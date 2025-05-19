#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t init_size = 1024;
    void *ptr = malloc(init_size);
    if (!ptr) {
        perror("Initial malloc failed");
        return 1;
    }

    strcpy(ptr, "Hello!");

    size_t huge_size = (size_t)-1;
    void *tmp = realloc(ptr, huge_size);

    if (tmp == NULL) {
        printf("Realloc failed. Old pointer still valid.\n");
        printf("Old content: %s\n", (char*)ptr);
        free(ptr);
    } else {
        ptr = tmp;
        printf("Realloc succeeded.\n");
        free(ptr);
    }

    return 0;
}
