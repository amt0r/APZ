#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    FILE *f = fopen(argv[2], "r");
    if (!f) return 1;

    char l[1024];
    while (fgets(l, sizeof(l), f))
        if (strstr(l, argv[1])) printf("%s", l);

    fclose(f);
    return 0;
}
