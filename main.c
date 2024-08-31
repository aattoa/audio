#include "buffer.h"
#include <stdio.h>

int main(void) {
    struct buffer buffer;
    if (buffer_read(&buffer, "test.txt") == buffer_ok) {
        fwrite(buffer.ptr, 1, buffer.len, stdout);
        buffer_free(&buffer);
    }
}
