#include <stdio.h>

#include "dynint.h"

void print_dynint(dynint a, char c) {
    printf("%c: ", c);
    for (size_t i = 0; a.size > i; i++) {
        printf("%d ", a.data[a.size - i - 1]);
    }

    printf("\n");
}

int main(int argc, char** argv) {
    uint64_t x = 0xFFFFFFFFFFFFFFFF;
    uint8_t y = 2;
    dynint a = dynint_init(sizeof(long), (uint8_t*)&x);
    dynint b = dynint_init(1, &y);
    print_dynint(a, 'a');
    print_dynint(b, 'b');

    a = dynint_div(a, b);
    print_dynint(a, 'a');

    return 0;
}
