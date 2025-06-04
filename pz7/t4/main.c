#include <stdio.h>

#define LINES 20
char buf[1024];

void show(const char *f) {
    FILE *fp = fopen(f, "r");
    if (!fp) return;
    int n = 0;
    while (fgets(buf, sizeof(buf), fp)) {
        fputs(buf, stdout);
        if (++n == LINES) {
            printf("== Press Enter ==");
            while (getchar() != '\n');
            n = 0;
        }
    }
    fclose(fp);
}

int main(int c, char **v) {
    if (c < 2) return 1;
    for (int i = 1; i < c; i++) {
        printf("\n-- %s --\n", v[i]);
        show(v[i]);
    }
    return 0;
}
