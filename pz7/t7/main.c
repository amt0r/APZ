#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int is_owned_exec(const char *f) {
    struct stat s;
    return !stat(f, &s) && S_ISREG(s.st_mode) && s.st_uid == getuid() && (s.st_mode & S_IXUSR);
}

int main() {
    DIR *d = opendir(".");
    if (!d) return 1;

    struct dirent *e;
    char r[8];

    while ((e = readdir(d))) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;
        if (!is_owned_exec(e->d_name)) continue;

        printf("Grant read to others for %s? (y/n): ", e->d_name);
        if (!fgets(r, sizeof(r), stdin)) continue;
        if (r[0] == 'y' || r[0] == 'Y') {
            struct stat s;
            if (!stat(e->d_name, &s) && chmod(e->d_name, s.st_mode | S_IROTH) == 0)
                printf("Granted: %s\n", e->d_name);
            else
                perror("chmod");
        } else {
            printf("Skipped: %s\n", e->d_name);
        }
    }

    closedir(d);
    return 0;
}
