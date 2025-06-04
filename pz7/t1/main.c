#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *rwho = popen("rwho", "r");
    FILE *more = popen("more", "w");
    char buf[256];

    if (!rwho || !more) {
        perror("popen");
        return 1;
    }

    while (fgets(buf, sizeof(buf), rwho))
        fputs(buf, more);

    pclose(rwho);
    pclose(more);
    return 0;
}
