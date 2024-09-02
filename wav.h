#ifndef AUDIO_WAV_H
#define AUDIO_WAV_H

#include "view.h"
#include <stdint.h>
#include <stdio.h>

struct wav_info {
    int32_t file_size;
    int32_t format_data_size;
    int32_t sample_rate;
    int32_t byte_rate;
    int16_t format_type;
    int16_t channel_count;
    int16_t bits_per_sample;
    int16_t block_alignment;
    size_t  data_offset;
};

enum wav_parse_status {
    wav_parse_ok,
    wav_parse_no_riff_marker,
    wav_parse_no_wav_marker,
    wav_parse_no_fmt_marker,
    wav_parse_no_data_marker,
    wav_parse_no_file_size,
    wav_parse_no_format_data_size,
    wav_parse_no_format_type,
    wav_parse_no_channel_count,
    wav_parse_no_sample_rate,
    wav_parse_no_bits_per_sample,
    wav_parse_no_byte_rate,
    wav_parse_no_block_align,
    wav_parse_no_list_size,
    wav_parse_bad_list_size,
};

enum wav_parse_status wav_parse(struct wav_info *output, struct view input);

const char *wav_parse_status_describe(enum wav_parse_status status);

void wav_info_display(FILE *stream, const struct wav_info *wav);

#endif // AUDIO_WAV_H
