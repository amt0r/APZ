#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void test_file_access(const char *filepath) {
    printf("\nFile check: %s\n", filepath);

    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        printf("Read: No (%s)\n", strerror(errno));
    } else {
        printf("Read: Yes\n");
        close(fd);
    }

    fd = open(filepath, O_WRONLY);
    if (fd == -1) {
        printf("Write: No (%s)\n", strerror(errno));
    } else {
        printf("Write: Yes\n");
        close(fd);
    }

    if (access(filepath, X_OK) == 0) {
        printf("Execute: Yes\n");
    } else {
        printf("Execute: No (%s)\n", strerror(errno));
    }
}

int main() {
    printf("View access rights:\n");

    printf("\nHome directory (~):\n");
    system("ls -l ~");

    printf("\n/usr/bin (first 10 files):\n");
    system("ls -l /usr/bin | head -n 10");

    printf("\n/etc (first 10 files):\n");
    system("ls -l /etc | head -n 10");


    test_file_access("/etc/passwd");  
    test_file_access("/etc/shadow"); 
    test_file_access("/usr/bin/ls"); 
    test_file_access("/usr/bin/cc"); 

    return 0;
}
