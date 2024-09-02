#include "buffer.h"
#include "util.h"
#include "view.h"
#include "wav.h"
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

void wav_test(struct view view) {
    struct wav_info wav;
    enum wav_parse_status status = wav_parse(&wav, view);
    if (status == wav_parse_ok) {
        wav_info_display(stdout, &wav);
    }
    else {
        printf("failed to parse wav info: %s\n", wav_parse_status_describe(status));
    }
}

void run_wav_test(void) {
    struct buffer buffer;
    if (buffer_read(&buffer, "test.wav") == buffer_ok) {
        wav_test(buffer_view(&buffer));
        buffer_free(&buffer);
    }
}

void sdl_die(void) {
    die("SDL error: %s\n", SDL_GetError());
}

void sdl_require(int code) {
    if (code != 0) {
        sdl_die();
    }
}

void *sdl_require_ptr(void *ptr) {
    if (ptr == NULL) {
        sdl_die();
    }
    return ptr;
}

void draw_bars(SDL_Renderer *renderer, int bars, int width, int height) {
    int bar_width = width / bars;
    int unit_height = height / bars;
    if (bar_width < 1 || unit_height < 1) {
        die("The window is too small");
    }
    for (int bar = 0; bar != bars; ++bar) {
        SDL_Rect rect = { .x = bar * bar_width, .y = 0, .w = bar_width, .h = bar * unit_height };
        sdl_require(SDL_RenderDrawRect(renderer, &rect));
    }
}

int main(void) {
    int width = 640;
    int height = 480;

    sdl_require(SDL_Init(SDL_INIT_VIDEO));
    SDL_Window *window = sdl_require_ptr(SDL_CreateWindow("audio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0));
    SDL_Renderer *renderer = sdl_require_ptr(SDL_CreateRenderer(window, -1, 0));

    sdl_require(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE));
    sdl_require(SDL_RenderClear(renderer));
    sdl_require(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE));
    draw_bars(renderer, width / 4, width, height);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

    SDL_Quit();
}
