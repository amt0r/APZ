#include <stdio.h>

void func_return() {
    // hand stack remove
    asm("addq $8, %rsp");
}

void func() {
    printf("Inside func()\n");
    func_return();
}

int main() {
    func();
    printf("Back in main()\n");
    return 0;
}
