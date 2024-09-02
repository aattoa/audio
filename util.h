#ifndef AUDIO_UTIL_H
#define AUDIO_UTIL_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

void die(const char *fmt, ...);

enum endianness { endianness_little, endianness_big };

enum endianness system_endianness(void);

int16_t read_i16(const void* data, enum endianness endianness);
int32_t read_i32(const void* data, enum endianness endianness);

void swap_byte_order(void *data, size_t size);

#endif // AUDIO_UTIL_H
