#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    pipe(pipefd);

    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    const int size = 1024 * 256;
    char *buf = malloc(size);
    memset(buf, 'A', size);

    ssize_t count = write(pipefd[1], buf, size);
    if (count < size)
        printf("write() wrote only %zd of %d bytes\n", count, size);

    free(buf);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
