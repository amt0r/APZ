#include <stdio.h>
#include <stdlib.h>

int main() {
    double original = 9876543.21;

    float *copy = (float *)malloc(sizeof(float));
    if (!copy) {
        printf("Memory allocation failed\n");
        return 1;
    }

    *copy = (float)original;

    printf("Original value: %.15f\n", original);
    printf("Copied value:   %.15f\n", *copy);

    free(copy);
    return 0;
}
