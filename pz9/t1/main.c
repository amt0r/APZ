#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define UID_MIN 1000

int main() {
    uid_t uid = getuid();
    struct passwd *me = getpwuid(uid);
    if (!me) return 1;

    FILE *fp = popen("getent passwd", "r");
    if (!fp) return 1;

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        char *user = strtok(line, ":");
        strtok(NULL, ":");
        int id = atoi(strtok(NULL, ":"));
        if (id >= UID_MIN && strcmp(user, me->pw_name)) {
            printf("%s (UID: %d)\n", user, id);
        }
    }

    pclose(fp);
    return 0;
}
