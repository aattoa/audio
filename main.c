#include "buffer.h"
#include "view.h"
#include "wav.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void display_wav_info(FILE *stream, const struct wav_info *wav) {
    fprintf(stream,
        "file_size:        %d\n"
        "format_data_size: %d\n"
        "sample_rate:      %d\n"
        "byte_rate:        %d\n"
        "format_type:      %d\n"
        "channel_count:    %d\n"
        "bits_per_sample:  %d\n"
        "block_alignment:  %d\n",
        (int)wav->file_size,
        (int)wav->format_data_size,
        (int)wav->sample_rate,
        (int)wav->byte_rate,
        (int)wav->format_type,
        (int)wav->channel_count,
        (int)wav->bits_per_sample,
        (int)wav->block_alignment);
}

void wav_test(struct view view) {
    struct wav_info wav;
    enum wav_parse_status status = wav_parse(&wav, view);
    if (status == wav_parse_ok) {
        display_wav_info(stdout, &wav);
    }
    else {
        printf("failed to parse wav info: %s\n", wav_parse_status_describe(status));
    }
}

int main(void) {
    struct buffer buffer;
    if (buffer_read(&buffer, "test.wav") == buffer_ok) {
        wav_test(buffer_view(&buffer));
        buffer_free(&buffer);
    }
}
