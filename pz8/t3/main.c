#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int is_sorted(int *a, int n) {
    for (int i = 1; i < n; i++)
        if (a[i - 1] > a[i]) return 0;
    return 1;
}

void fill(int *a, int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == 0) a[i] = i;             // sorted
        if (type == 1) a[i] = n - i;         // reverse
        if (type == 2) a[i] = 42;            // constant
        if (type == 3) a[i] = i % 5;         // patterned
        if (type == 4) a[i] = rand();        // random
    }
}

void test(const char *name, int type) {
    int *a = malloc(N * sizeof(int));
    fill(a, N, type);
    clock_t t = clock();
    qsort(a, N, sizeof(int), cmp);
    t = clock() - t;
    printf("%s: %.3fs, sorted: %s\n", name, (double)t / CLOCKS_PER_SEC, is_sorted(a, N) ? "yes" : "no");
    free(a);
}

int main() {
    srand(time(NULL));
    test("Sorted", 0);
    test("Reverse", 1);
    test("Constant", 2);
    test("Patterned", 3);
    test("Random", 4);
    return 0;
}
