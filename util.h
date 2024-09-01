#ifndef AUDIO_UTIL_H
#define AUDIO_UTIL_H

#include <stdint.h>
#include <assert.h>

void die(const char *fmt, ...);

int16_t read_le_i16(const void *data);

int32_t read_le_i32(const void *data);

#endif // AUDIO_UTIL_H
