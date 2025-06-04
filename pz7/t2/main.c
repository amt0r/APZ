#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

void print_mode(mode_t mode) {
    char types[] = "?pc?d?b?-?l?s?";
    printf("%c", types[(mode >> 12) & 0xF]);
    char perms[] = "rwxrwxrwx";
    for (int i = 0; i < 9; ++i)
        printf("%c", (mode & (1 << (8 - i))) ? perms[i] : '-');
}

int main() {
    DIR *d = opendir(".");
    if (!d) return 1;
    struct dirent *e;
    struct stat s;
    char timebuf[20];

    while ((e = readdir(d))) {
        if (e->d_name[0] == '.') continue;
        if (lstat(e->d_name, &s) == -1) continue;

        print_mode(s.st_mode);
        printf(" %lu ", s.st_nlink);
        printf("%s %s ", getpwuid(s.st_uid)->pw_name, getgrgid(s.st_gid)->gr_name);
        printf("%5lld ", (long long)s.st_size);
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&s.st_mtime));
        printf("%s %s\n", timebuf, e->d_name);
    }

    closedir(d);
    return 0;
}
