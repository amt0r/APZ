#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int is_dir(const char *n) {
    struct stat s;
    return stat(n, &s) == 0 && S_ISDIR(s.st_mode);
}

int cmp(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    DIR *d = opendir(".");
    if (!d) return 1;

    struct dirent *e;
    char *list[1024];
    int count = 0;

    while ((e = readdir(d)))
        if (strcmp(e->d_name, ".") && strcmp(e->d_name, "..") && is_dir(e->d_name))
            list[count++] = strdup(e->d_name);

    closedir(d);

    qsort(list, count, sizeof(char *), cmp);

    for (int i = 0; i < count; i++) {
        printf("%s/\n", list[i]);
        free(list[i]);
    }

    return 0;
}
