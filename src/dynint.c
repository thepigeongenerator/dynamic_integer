#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "dynint.h"

dynint dynint_init(const size_t c, const uint8_t* value) {
    const size_t size = c > 0 ? c * sizeof(uint8_t) : 1; // set the initial size to 1 or the inputted count
    uint8_t* data = malloc(size);                        // allocate the bytes for the integer

    // copy the data from the inputted value
    for (size_t i = 0; i < c; i++) {
        data[i] = value[i];
    }

    // return the dynamic integer
    return (dynint){size, data};
}

dynint dynint_add(dynint a, dynint b) {
    const size_t size = ((a.size > b.size) ? a.size : b.size) + 1; // get which dynint is larger, add one for carrying
    uint8_t* res = malloc(size);                                   // allocate an array of bytes which will contain the result
    uint8_t buf = 0;                                               // buffer byte, for carrying
    dynint out = {0};                                              // output

    // loop through the size of the result
    for (size_t i = 0; i < size; i++) {
        uint16_t tot = buf;

        // add the data if it is within the size
        if (i < a.size)
            tot += a.data[i];
        if (i < b.size)
            tot += b.data[i];

        res[i] = tot;   // uin16 is implicitally truncated to uint8
        buf = tot >> 8; // store the bits we missed.
    }

    // if the remainder is 0, we don't need this final byte
    if (buf == 0)
        out = dynint_init(size - 1, res);
    else
        out = dynint_init(size, res);
    free(res);
    return out;
}
