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

// TODO: handle byteswap for big endian machines

int16_t read_le_i16(const void *data) {
    return *(const int16_t*)data;
}

int32_t read_le_i32(const void *data) {
    return *(const int32_t*)data;
}
