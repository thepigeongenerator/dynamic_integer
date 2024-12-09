#include <stdint.h>
#include <stdlib.h>

// contains the pointer to the dynamic integer's data array and the size in bytes of the integer
typedef struct {
    size_t size;
    uint8_t* data;
} dynint;

dynint dynint_init(const size_t c, const uint8_t* value);
dynint dynint_add(dynint a, dynint b);
dynint dynint_sub(dynint a, dynint b);
dynint dynint_div(dynint a, dynint b);
dynint dynint_mlt(dynint a, dynint b);
dynint dynint_mod(dynint a, dynint b);
