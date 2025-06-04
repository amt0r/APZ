#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    float n = (argc == 2) ? atof(argv[1]) : 1.0;
    if (n <= 0) { fprintf(stderr, "n must be > 0\n"); return 1; }

    srand((unsigned)time(NULL));
    for (int i = 0; i < 5; i++) printf("0.0–1.0: %.6f\n", (float)rand()/RAND_MAX);
    for (int i = 0; i < 5; i++) printf("0.0–%.2f: %.6f\n", n, ((float)rand()/RAND_MAX)*n);

    return 0;
}
