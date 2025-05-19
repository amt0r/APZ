#include <stdio.h>

void recurse(int depth) {
    char buffer[1024];
    printf("Depth: %d | Address: %p\n", depth, (void *)&buffer);
    recurse(depth + 1);
}

int main() {
    recurse(1);
    return 0;
}
