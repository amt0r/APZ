//18
// Напишіть функцію, яка друкує 8-бітне (беззнакове) число у двійковому форматі.
// Реалізуйте дві версії:
// З використанням бітових операцій (&, |, <<, >>).
// Через табличний метод для пришвидшення обчислень.
// Додайте можливість друку 16-бітних, 32-бітних і 64-бітних чисел.
// Реалізуйте форматований вивід (printf) для вирівнювання та відображення у вигляді блоків (наприклад, 0000 1111 1010 0101).
// Додайте функцію конвертації тексту у двійковий код ASCII

// Byte = 8 bits
// 7 6 5 4 3 2 1 0 (Most Significant Bit → Least Significant Bit)
// 0x - hex
// LSB → MSB (Least Significant Byte → Most Significant Byte), depent on architecture

#include <stdio.h>
#include <stdint.h>

void print_binary(uint64_t num, int bits) {
    for(int i = bits - 1; i>=0; i--) {
        printf("%d", (num & ((uint64_t) 1 << i) ? 1 : 0));
        if (i % 4 == 0) printf("\t");
    }
    printf("\n");
}

void text_to_binary(const char *text) {
    while (*text) {
        print_binary(*text, 7);
        text++;
    }
}

char *binary_table[256];

void init_binary_table() {
    static char buffer[256][9];
    for (int i = 0; i < 256; i++) {
        for (int j = 7; j >= 0; j--) {
            buffer[i][7 - j] = (i & (1 << j)) ? '1' : '0';
        }
        buffer[i][8] = '\0';
        binary_table[i] = buffer[i];
    }
}

void print_binary_table(uint8_t num) {
    printf("%s\n", binary_table[num]);
}

int main() {
    init_binary_table();

    uint8_t num8 = 4;
    uint16_t num16 = 42132;
    uint32_t num32 = 132132454;
    uint64_t num64 = 0xFFFFFFFFFFFFFFFF;

    printf("8-bit:\t"); print_binary(num8, 8);
    printf("16-bit:\t"); print_binary(num16, 16);
    printf("32-bit:\t"); print_binary(num32, 32);
    printf("64-bit:\t"); print_binary(num64, 64);

    printf("\nTable fun 8-bit:\t");
    print_binary_table(num8);

    printf("\nASCII:\n");
    text_to_binary("Hello");

    return 0;
}