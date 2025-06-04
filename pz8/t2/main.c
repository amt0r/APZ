#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buf[4];

    int fd = open("file.bin", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write(fd, data, sizeof(data));
    close(fd);

    fd = open("file.bin", O_RDONLY);
    lseek(fd, 3, SEEK_SET);
    read(fd, buf, 4);
    close(fd);

    for (int i = 0; i < 4; i++)
        printf("%d ", buf[i]);
    printf("\n");
}
