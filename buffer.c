#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum buffer_status buffer_allocate(struct buffer *buffer, size_t len) {
    if (len == 0) {
        return buffer_bad_malloc;
    }
    void *ptr = malloc(len);
    if (ptr == NULL) {
        return buffer_bad_malloc;
    }
    buffer->len = len;
    buffer->ptr = ptr;
    return buffer_ok;
}

enum buffer_status buffer_read_stream(struct buffer *buffer, FILE *stream) {
    if (fseek(stream, 0, SEEK_END) != 0) {
        return buffer_bad_read;
    }
    long size = ftell(stream);
    if (size < 1) {
        return buffer_bad_read;
    }
    rewind(stream);
    enum buffer_status buffer_status = buffer_allocate(buffer, size);
    if (buffer_status != buffer_ok) {
        return buffer_status;
    }
    if (fread(buffer->ptr, 1, size, stream) != (size_t)size) {
        buffer_free(buffer);
        return buffer_bad_read;
    }
    return buffer_ok;
}

enum buffer_status buffer_read(struct buffer *buffer, const char *path) {
    FILE *stream = fopen(path, "rb");
    if (stream == NULL) {
        return buffer_bad_path;
    }
    enum buffer_status buffer_status = buffer_read_stream(buffer, stream);
    fclose(stream);
    return buffer_status;
}

enum buffer_status buffer_copy(struct buffer *destination, struct buffer *source) {
    enum buffer_status buffer_status = buffer_allocate(destination, source->len);
    if (buffer_status == buffer_ok) {
        memcpy(destination->ptr, source->ptr, source->len);
    }
    return buffer_status;
}

void buffer_free(struct buffer *buffer) {
    if (buffer->ptr) {
        free(buffer->ptr);
        buffer->ptr = NULL;
    }
}
