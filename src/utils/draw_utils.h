#ifndef DRAW_UTILS_H_
#define DRAW_UTILS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void draw_text(SDL_Renderer *renderer, char *text, int x, int y);
void draw_wave_form(SDL_Renderer *renderer, SDL_Rect *bounds, float *buffer, int buffer_size);
void draw_slider(SDL_Renderer *renderer, char *label, int x, int y, int size, float value, float min, float max);

#endif