#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));
    *ptr = 123;

    free(ptr);

    printf("Use after free: %d\n", *ptr);

    return 0;
}
