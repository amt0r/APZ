#Task 18
Напишіть функцію, яка друкує 8-бітне (беззнакове) число у двійковому форматі.
Реалізуйте дві версії:
З використанням бітових операцій (&, |, <<, >>).
Через табличний метод для пришвидшення обчислень.
Додайте можливість друку 16-бітних, 32-бітних і 64-бітних чисел.
Реалізуйте форматований вивід (printf) для вирівнювання та відображення у вигляді блоків (наприклад, 0000 1111 1010 0101).
Додайте функцію конвертації тексту у двійковий код ASCII
---

#About program
##This program has the following functions:
Function for conveting num to binary num and print it.
print_binary(uint64_t num, int bits)

Function for conveting ASCII letters to binary num and print it.
text_to_binary(const char *text)

Function for conveting num to binary num and print it, but using table(needed initilize init_binary_table()).
print_binary_table(uint8_t num)

#How to use
Compile and run
```c
cd "direcrtion_to_file" && clang to_binary.c -o to_binary && "destionation_direction"to_binary

#Some facts
Byte = 8 bits
Order of bits in the byte: 7 6 5 4 3 2 1 0 (Most Significant Bit → Least Significant Bit)
Prefix: "0x" mean hex number
Order of bytes: LSB → MSB (Least Significant Byte → Most Significant Byte), order depent on architecture