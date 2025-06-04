#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();
    printf("pid = %d, my pid = %d\n", pid, getpid());
    return 0;
}
