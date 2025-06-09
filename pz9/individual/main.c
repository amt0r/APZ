#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void try_read_file(const char *filename) {
    printf("User tries to read %s\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Failed to open file for reading: %s\n", strerror(errno));
    } else {
        printf("File content:\n");
        char buf[256];
        while (fgets(buf, sizeof(buf), f)) {
            printf("%s", buf);
        }
        fclose(f);
        printf("\n");
    }
}

int main() {
    const char *confidential = "/home/amtor/Desktop/APZ/pz9/individual/confidential";
    const char *copy = "/home/amtor/Desktop/APZ/pz9/individual/confidential_copy";

    uid_t uid = getuid();
    printf("Running as UID=%d\n\n", uid);

    if (uid == 0) {
        printf("Root creating confidential file...\n");
        int fd = open(confidential, O_WRONLY | O_CREAT | O_TRUNC, 0200); // --w-------
        if (fd < 0) {
            perror("Failed to create confidential file");
            return 1;
        }
        const char *secret = "Top secret information\n";
        write(fd, secret, strlen(secret));
        close(fd);
        printf("File created with permissions 0200 (write only by root).\n\n");

        printf("Root copying file for user access...\n");
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cp %s %s && chmod 644 %s && chown 1000:1000 %s", confidential, copy, copy, copy);
        system(cmd);
        printf("Copy created with permissions 644 for user.\n");

    } else if (uid == 1000) {
        try_read_file(confidential);

        try_read_file(copy);

    } else {
        printf("Run as root or user with UID=1000 (amtor).\n");
    }

    return 0;
}
