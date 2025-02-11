// %02X - fill with zeros, 2 digit, X - hex upper case

#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t num = 0xF5A3;
    uint8_t *ptr = (uint8_t *)&num;

    printf("Byte order in memory: %02X %02X\n", ptr[0], ptr[1]);
    return 0;
}
