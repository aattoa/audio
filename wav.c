#include "wav.h"
#include "util.h"

enum wav_parse_status wav_parse(struct wav_info *output, struct view input) {
    const char *anchor = input.ptr;
    if (!view_remove_prefix(&input, view_from("RIFF"))) { // 1-4
        return wav_parse_no_riff_marker;
    }
    const void *file_size_i32 = input.ptr;
    if (!view_remove_prefix_n(&input, 4)) { // 5-8
        return wav_parse_no_file_size;
    }
    if (!view_remove_prefix(&input, view_from("WAVE"))) { // 9-12
        return wav_parse_no_wav_marker;
    }
    if (!view_remove_prefix(&input, view_from("fmt "))) { // 13-16
        return wav_parse_no_fmt_marker;
    }
    const void *format_data_size_i32 = input.ptr;
    if (!view_remove_prefix_n(&input, 4)) { // 17-20
        return wav_parse_no_format_data_size;
    }
    const void *format_type_i16 = input.ptr;
    if (!view_remove_prefix_n(&input, 2)) { // 21-22
        return wav_parse_no_format_type;
    }
    const void *channel_count_i16 = input.ptr;
    if (!view_remove_prefix_n(&input, 2)) { // 23-24
        return wav_parse_no_channel_count;
    }
    const void *sample_rate_i32 = input.ptr;
    if (!view_remove_prefix_n(&input, 4)) { // 25-28
        return wav_parse_no_sample_rate;
    }
    const void *byte_rate_i32 = input.ptr;
    if (!view_remove_prefix_n(&input, 4)) { // 29-32
        return wav_parse_no_byte_rate;
    }
    const void *block_align_i16 = input.ptr;
    if (!view_remove_prefix_n(&input, 2)) { // 33-34
        return wav_parse_no_block_align;
    }
    const void *bits_per_sample_i16 = input.ptr;
    if (!view_remove_prefix_n(&input, 2)) { // 35-36
        return wav_parse_no_bits_per_sample;
    }
    if (view_remove_prefix(&input, view_from("LIST"))) {
        const void *list_size_i32 = input.ptr;
        if (!view_remove_prefix_n(&input, 4)) {
            return wav_parse_no_list_size;
        }
        if (!view_remove_prefix_n(&input, read_i32(list_size_i32, endianness_little))) {
            return wav_parse_bad_list_size;
        }
    }
    if (!view_remove_prefix(&input, view_from("data"))) {
        return wav_parse_no_data_marker;
    }
    output->file_size        = read_i32(file_size_i32, endianness_little);
    output->format_data_size = read_i32(format_data_size_i32, endianness_little);
    output->sample_rate      = read_i32(sample_rate_i32, endianness_little);
    output->byte_rate        = read_i32(byte_rate_i32, endianness_little);
    output->format_type      = read_i16(format_type_i16, endianness_little);
    output->channel_count    = read_i16(channel_count_i16, endianness_little);
    output->block_alignment  = read_i16(block_align_i16, endianness_little);
    output->bits_per_sample  = read_i16(bits_per_sample_i16, endianness_little);
    output->data_offset      = input.ptr - anchor;
    return wav_parse_ok;
}

const char *wav_parse_status_describe(enum wav_parse_status status) {
    switch (status) {
    case wav_parse_ok:                  return "ok";
    case wav_parse_no_riff_marker:      return "no_riff_marker";
    case wav_parse_no_wav_marker:       return "no_wav_marker";
    case wav_parse_no_fmt_marker:       return "no_fmt_marker";
    case wav_parse_no_data_marker:      return "no_data_marker";
    case wav_parse_no_file_size:        return "no_file_size";
    case wav_parse_no_format_data_size: return "no_format_data_size";
    case wav_parse_no_format_type:      return "no_format_type";
    case wav_parse_no_channel_count:    return "no_channel_count";
    case wav_parse_no_sample_rate:      return "no_sample_rate";
    case wav_parse_no_bits_per_sample:  return "no_bits_per_sample";
    case wav_parse_no_byte_rate:        return "no_byte_rate";
    case wav_parse_no_block_align:      return "no_block_align";
    case wav_parse_no_list_size:        return "no_list_size";
    case wav_parse_bad_list_size:       return "bad_list_size";
    default:                            return "unknown parse status";
    }
}

void wav_info_display(FILE *stream, const struct wav_info *wav) {
    fprintf(stream,
        "file_size:        %d\n"
        "format_data_size: %d\n"
        "sample_rate:      %d\n"
        "byte_rate:        %d\n"
        "format_type:      %d\n"
        "channel_count:    %d\n"
        "bits_per_sample:  %d\n"
        "block_alignment:  %d\n"
        "data_offset:      %d\n",
        (int)wav->file_size,
        (int)wav->format_data_size,
        (int)wav->sample_rate,
        (int)wav->byte_rate,
        (int)wav->format_type,
        (int)wav->channel_count,
        (int)wav->bits_per_sample,
        (int)wav->block_alignment,
        (int)wav->data_offset);
}
