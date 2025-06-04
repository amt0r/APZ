#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval s, e;
    gettimeofday(&s, NULL);

    for (volatile long i = 0; i < 100000000; ++i);

    gettimeofday(&e, NULL);
    long ms = (e.tv_sec - s.tv_sec) * 1000 + (e.tv_usec - s.tv_usec) / 1000;
    printf("Time: %ld ms\n", ms);
    return 0;
}
