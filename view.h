#ifndef AUDIO_VIEW_H
#define AUDIO_VIEW_H

#include <stddef.h>
#include <stdbool.h>

struct view {
    size_t len;
    const char *ptr;
};

struct view view_from(const char *string);

bool view_deep_equal(struct view lhs, struct view rhs);

bool view_starts_with(struct view view, struct view prefix);

bool view_ends_with(struct view view, struct view suffix);

bool view_extract_prefix(struct view *view, size_t length, char *buffer);

bool view_extract_suffix(struct view *view, size_t length, char *buffer);

bool view_remove_prefix_n(struct view *view, size_t n);

bool view_remove_prefix(struct view *view, struct view prefix);

bool view_remove_suffix_n(struct view *view, size_t n);

bool view_remove_suffix(struct view *view, struct view suffix);

void view_remove_prefix_unchecked(struct view *view, size_t n);

void view_remove_suffix_unchecked(struct view *view, size_t n);

#endif // AUDIO_VIEW_H
