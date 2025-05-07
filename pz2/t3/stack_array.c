#include <stdio.h>

int global_var = 10; // data segment

int main() {
    int i; // stack
    int local_array[10000];  // stack (huge array)
    int x; // stack

    printf("The address of the global variable: %p\n", &global_var);
    printf("The address of a local variable (before array): %p\n", &x);
    printf("The address of the local array: %p\n", local_array);
    printf("The address of a local variable (after array): %p\n", &i);
    return 0;
}