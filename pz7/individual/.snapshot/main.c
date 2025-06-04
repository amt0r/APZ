#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    system("mkdir -p .snapshot && rsync -a --delete ./ .snapshot/");

    char cmd[1024] = {0};
    for (int i = 1; i < argc; i++) {
        strcat(cmd, argv[i]);
        if (i < argc - 1) strcat(cmd, " ");
    }
    system(cmd);

    printf("Rewind? (y/n): ");
    char ans[4];
    if (fgets(ans, sizeof(ans), stdin) && (ans[0] == 'y' || ans[0] == 'Y')) {
        system("rsync -a --delete .snapshot/ ./ && echo \"Rewound.\"");
    }

    return 0;
}
