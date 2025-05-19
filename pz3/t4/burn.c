#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <signal.h>

#define OUT_FILE "lottery_result.txt"

void cpu_time_exceeded(int sig) {
    fprintf(stderr, "CPU time limit exceeded. Exiting.\n");
    exit(1);
}

void generate_unique_numbers(int count, int max, int *out) {
    int used[max + 1];
    for (int i = 0; i <= max; i++) used[i] = 0;
    int num, i = 0;
    while (i < count) {
        num = rand() % max + 1;
        if (!used[num]) {
            used[num] = 1;
            out[i++] = num;
        }
    }
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void burn_cpu_time() {
    volatile double x = 0;
    for (long long i = 0; i < 1e9; i++) {
        x += i * 0.0000001;
    }
}

int main() {
    struct rlimit rl;
    rl.rlim_cur = 1;
    rl.rlim_max = 2;
    setrlimit(RLIMIT_CPU, &rl);
    signal(SIGXCPU, cpu_time_exceeded);
    srand(time(NULL));

    int main_numbers[7];
    int bonus_numbers[6];

    generate_unique_numbers(7, 49, main_numbers);
    generate_unique_numbers(6, 36, bonus_numbers);

    qsort(main_numbers, 7, sizeof(int), compare);
    qsort(bonus_numbers, 6, sizeof(int), compare);

    FILE *f = fopen(OUT_FILE, "w");
    if (!f) {
        perror("Failed to open output file");
        return 1;
    }

    fprintf(f, "Main numbers (7 of 49): ");
    for (int i = 0; i < 7; i++) fprintf(f, "%d ", main_numbers[i]);

    fprintf(f, "\nBonus numbers (6 of 36): ");
    for (int i = 0; i < 6; i++) fprintf(f, "%d ", bonus_numbers[i]);
    fprintf(f, "\n");

    fclose(f);
    printf("Results saved to %s\n", OUT_FILE);

    printf("Now burning CPU time...\n");
    burn_cpu_time();

    return 0;
}