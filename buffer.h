#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include "view.h"
#include <stddef.h>
#include <stdio.h>

struct buffer {
    size_t len;
    char *ptr;
};

enum buffer_status {
    buffer_ok,         // Everything is fine
    buffer_bad_malloc, // Could not allocate memory
    buffer_bad_path,   // Could not open the file
    buffer_bad_read,   // Could not read the file
};

enum buffer_status buffer_allocate(struct buffer *buffer, size_t len);

enum buffer_status buffer_read_stream(struct buffer *buffer, FILE *stream);

enum buffer_status buffer_read(struct buffer *buffer, const char *path);

enum buffer_status buffer_copy(struct buffer *destination, struct buffer *source);

struct view buffer_view(struct buffer *buffer);

void buffer_free(struct buffer *buffer);

#endif // AUDIO_BUFFER_H
