#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filepath = "mapped_file.bin";
    size_t length = 4096;

    int fd = open(filepath, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (ftruncate(fd, length) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    void *addr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    close(fd);

    strcpy((char *)addr, "Data that survives program termination.");

    printf("Data written to mapped memory: %s\n", (char *)addr);

    return 0;
}
