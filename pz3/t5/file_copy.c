#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 1000000

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (!dst) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(src);
        return 1;
    }

    char buffer[1024];
    size_t total_written = 0;

    while (1) {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), src);
        if (bytes_read == 0) break;

        if (total_written + bytes_read > MAX_FILE_SIZE) {
            printf("File size limit exceeded (%d bytes)\n", MAX_FILE_SIZE);
            fclose(src);
            fclose(dst);
            remove(argv[2]);
            return 1;
        }

        fwrite(buffer, 1, bytes_read, dst);
        total_written += bytes_read;
    }

    fclose(src);
    fclose(dst);
    return 0;
}
