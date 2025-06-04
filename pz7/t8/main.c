#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int is_regular(const char *f) {
    struct stat s;
    return !stat(f, &s) && S_ISREG(s.st_mode);
}

int main() {
    DIR *d = opendir(".");
    struct dirent *e;
    char r[4];

    if (!d) return 1;

    while ((e = readdir(d))) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;
        if (!is_regular(e->d_name)) continue;

        printf("Delete '%s'? (y/n): ", e->d_name);
        if (!fgets(r, sizeof(r), stdin)) continue;
        if (r[0] == 'y' || r[0] == 'Y') {
            if (!remove(e->d_name))
                printf("Deleted: %s\n", e->d_name);
            else
                perror(e->d_name);
        } else {
            printf("Skipped: %s\n", e->d_name);
        }
    }

    closedir(d);
    return 0;
}
