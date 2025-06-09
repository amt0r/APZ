#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void check_rw(const char *filename) {
    printf("Check file access as current user (UID=%d)\n", getuid());
    if (access(filename, R_OK) == 0) {
        printf("Can read file\n");
    } else {
        printf("Can't read file: %s\n", strerror(errno));
    }
    if (access(filename, W_OK) == 0) {
        printf("Can write file\n");
    } else {
        printf("Can't write file: %s\n", strerror(errno));
    }
}

int main() {
    const char *filename = "/home/amtor/testfile_tmp.txt";

    printf("UID of current user: %d\n", getuid());

    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        perror("File creation error");
        return 1;
    }
    write(fd, "This is a temp file.\n", 21);
    close(fd);
    printf("File %s created.\n", filename);

    system("chown root:root /home/amtor/testfile_tmp.txt");
    system("chmod 644 /home/amtor/testfile_tmp.txt");

    printf("Checking access as root:\n");
    check_rw(filename);

    if (setuid(1000) < 0) {
        perror("Failed to switch to UID=1000");
        return 1;
    }

    printf("Switched to UID=%d\n", getuid());
    printf("Checking access as user 1000:\n");
    check_rw(filename);

    return 0;
}
