#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    time_t max_time;

    if ((time_t)-1 < 0) {
        // time_t is signed
        max_time = (time_t)((1ULL << (sizeof(time_t) * 8 - 1)) - 1); //ULL - Unsigned Long Long
    } else {
        // time_t is unsigned
        max_time = (time_t)(~(time_t)0); //~ - not
    }

    printf("Maximum value of time_t: %lld\n", (long long)max_time);

    printf("Date and time when time_t overflows (UTC): %s\n", ctime(&max_time));

    return 0;
}
// -m32 for x32 compile