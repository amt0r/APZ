#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <errno.h>

#define LINE_LEN 256

unsigned long get_first_address(pid_t pid) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/maps", pid);
    FILE *maps = fopen(path, "r");
    if (!maps) {
        perror("fopen maps");
        return 0;
    }

    char line[LINE_LEN];
    if (fgets(line, LINE_LEN, maps) == NULL) {
        perror("fgets");
        fclose(maps);
        return 0;
    }

    fclose(maps);

    unsigned long addr = 0;
    sscanf(line, "%lx-", &addr);  // take first addr
    return addr;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Використання: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    unsigned long addr = get_first_address(pid);
    if (!addr) {
        fprintf(stderr, "Не вдалося отримати адресу пам’яті\n");
        return 1;
    }

    printf("Читання з адреси: 0x%lx\n", addr);

    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
        perror("ptrace attach");
        return 1;
    }

    waitpid(pid, NULL, 0);

    long data = ptrace(PTRACE_PEEKDATA, pid, (void *)addr, NULL);
    if (data == -1) {
        perror("ptrace peekdata");
    } else {
        printf("Дані з адреси 0x%lx: 0x%lx\n", addr, data);
    }

    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    return 0;
}
// ps aux | grep firefox
