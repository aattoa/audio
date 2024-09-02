#include "util.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void die(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

enum endianness system_endianness(void) {
    int x = 1;
    return (x == *(char*)&x) ? endianness_little : endianness_big;
}

int16_t read_i16(const void* data, enum endianness endianness) {
    int16_t value = *(const int16_t*)data;
    if (system_endianness() != endianness) {
        swap_byte_order(&value, sizeof value);
    }
    return value;
}

int32_t read_i32(const void* data, enum endianness endianness) {
    int32_t value = *(const int32_t*)data;
    if (system_endianness() != endianness) {
        swap_byte_order(&value, sizeof value);
    }
    return value;
}

void swap_byte_order(void *data, size_t size) {
    assert(data != NULL && size != 0);
    for (char *a = data, *b = a + size - 1; a < b; ++a, --b) {
        char c = *b;
        *b = *a;
        *a = c;
    }
}
