#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void list(const char *p) {
    DIR *d = opendir(p);
    if (!d) return;
    struct dirent *e;
    char f[1024];
    while ((e = readdir(d))) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;
        snprintf(f, sizeof(f), "%s/%s", p, e->d_name);
        struct stat s;
        if (stat(f, &s) == 0) {
            if (S_ISDIR(s.st_mode)) list(f);
            else puts(f);
        }
    }
    closedir(d);
}

int main() {
    list(".");
    return 0;
}
