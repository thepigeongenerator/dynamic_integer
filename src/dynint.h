#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// contains the pointer to the dynamic integer's data array and the size in bytes of the integer
typedef struct {
    size_t size;
    uint8_t* data;
    bool neg;
} dynint;

void dynint_shrink(dynint* val);
dynint dynint_init(const size_t c, const uint8_t* value, const bool neg);
dynint dynint_add(const dynint a, const dynint b);
dynint dynint_sub(const dynint a, const dynint b);
dynint dynint_div(const dynint a, const dynint b);
dynint dynint_mlt(const dynint a, const dynint b);
dynint dynint_mod(const dynint a, const dynint b);
