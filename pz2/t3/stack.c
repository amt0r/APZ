#include <stdio.h>

int global_var = 10; // data segment

int main() {
    int local_var = 20; // stack (local var)
    int i; // stack

    printf("The address of the global variable: %p\n", &global_var);
    printf("The address of the local variable: %p\n", &local_var);
    printf("The address of the stack (local variable): %p\n", &i);

    return 0;
}
