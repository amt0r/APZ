#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    char path[256], fdinfo[256], line[256];
    DIR *dir;
    FILE *fp;
    struct dirent *entry;

    snprintf(path, sizeof(path), "/proc/%s/fd", argv[1]);
    dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] < '0' || entry->d_name[0] > '9') continue;

        snprintf(fdinfo, sizeof(fdinfo), "/proc/%s/fdinfo/%s", argv[1], entry->d_name);
        fp = fopen(fdinfo, "r");
        if (!fp) continue;

        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "pos:", 4) == 0) {
                printf("fd %s offset %s", entry->d_name, line + 5);
                break;
            }
        }

        fclose(fp);
    }

    closedir(dir);
    return 0;
}
