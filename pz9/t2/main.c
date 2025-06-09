#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    int status = system("sudo cat /etc/shadow");
    if (status == -1 || WEXITSTATUS(status)) {
        fprintf(stderr, "Failed to read /etc/shadow. Are you allowed to use sudo?\n");
        return 1;
    }
    return 0;
}
