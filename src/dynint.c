#include "dynint.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// shrinks the space allocated to the binary integer to the least amount of size necessary.
void dynint_shrink(dynint* val) {
    size_t size = val->size;

    while (size > 1 && val->data[size - 1] == 0)
        size--;

    // reallocate the data to the new size
    val->data = realloc(val->data, size);
}

dynint dynint_init(const size_t c, const uint8_t* value, const bool neg) {
    // initial size is 1 or the smallest size of the inputted value
    size_t size = c;
    while (size > 1 && value[size - 1] == 0)
        size--;

    uint8_t* data = malloc(size); // allocate bytes for the integer
    memcpy(data, value, size);

    // return the dynamic integer
    dynint i = {size, data, neg};
    dynint_shrink(&i);
    return i;
}

// adds a to b
dynint dynint_add(const dynint a, const dynint b) {
    const size_t size = ((a.size > b.size) ? a.size : b.size) + 1; // get which dynint is larger, add one for carrying
    uint8_t* res = malloc(size);                                   // allocate an array of bytes which will contain the result
    uint8_t buf = 0;                                               // buffer byte, for carrying

    // loop through the size of the result
    for (size_t i = 0; i < size; i++) {
        uint16_t tot = buf;

        // add the data if it is within the size
        if (i < a.size)
            tot += a.data[i];
        if (i < b.size)
            tot += a.data[i];

        res[i] = tot;   // uin16 is implicitally truncated to uint8
        buf = tot >> 8; // store the bits we missed.
    }

    // if the remainder is 0, we don't need this final byte, so reallocate the array
    if (buf == 0) {
        dynint out = dynint_init(size - 1, res, a.neg ^ b.neg);
        free(res);
        return out;
    }

    return (dynint){size, res, a.neg ^ b.neg};
}

// subtracts a from b
dynint dynint_sub(const dynint a, const dynint b) {
    dynint c = a;
    c.neg = !c.neg; // invert one of the the values
    return dynint_add(c, b);
}

// multiplies a with b
dynint dynint_mlt(const dynint a, const dynint b) {
    size_t size = a.size + b.size; // get which dynint is larger, add one for carrying (close to the worst-case scenario)
    uint8_t* res = malloc(size);   // allocate an array of bytes which will contain the result

    for (size_t i = 0; i < a.size; i++) {
        uint8_t buf = 0; // buffer byte, for carrying

        for (size_t j = 0; j < b.size; j++) {
            size_t k = i + j;

            // get the product
            uint16_t prod = (a.data[i] * b.data[j]) + res[k] + buf;

            res[k] = prod;   // implicitally truncates to uint8
            buf = prod >> 8; // store the buffer
        }
    }


    dynint out = dynint_init(size, res, a.neg ^ b.neg);
    free(res);
    return out;
}

// divide a by b
dynint dynint_div(const dynint a, const dynint b) {
    fprintf(stderr, "\033[91mdynint_div is not implemented\033[0m\n");
    exit(1);
}
