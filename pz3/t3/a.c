#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILE_SIZE 1000

int roll_dice() {
    return rand() % 6 + 1;
}

long get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

int main() {
    const char *filename = "dice_rolls.txt";
    FILE *file = fopen(filename, "a+");
    if (!file) {
        perror("File open error");
        return 1;
    }

    srand(time(NULL));

    while (1) {
        int roll = roll_dice();
        char line[10];
        int len = snprintf(line, sizeof(line), "%d\n", roll);

        long current_size = get_file_size(file);

        if (current_size + len > MAX_FILE_SIZE) {
            printf("Reached the limit of file (%d byte). Stop writing.\n", MAX_FILE_SIZE);
            break;
        }

        fputs(line, file);
        fflush(file);
    }

    fclose(file);
    return 0;
}
