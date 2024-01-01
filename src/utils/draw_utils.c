#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "math_utils.h"
#include "../../lib/SDL_inprint/SDL2_inprint.h"

void draw_text(SDL_Renderer *renderer, char *text, int x, int y)
{
    incolor(0x000000, 0);
    inprint(renderer, text, x, y);
}

void draw_wave_form(SDL_Renderer *renderer, SDL_Rect *bounds, float *buffer, int buffer_size)
{

    for (int i = 0; i < bounds->w; i++)
    {
        int remaped_index = (buffer_size / bounds->w) * i;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, bounds->x + i, (bounds->y - bounds->h / 2) + (buffer[remaped_index] * bounds->h / 2));
    }
}

void draw_slider(SDL_Renderer *renderer, char *label, int x, int y, int size, float value, float min, float max)
{

    draw_text(renderer, label, x, y);

    int remaped_value = remap(value, min, max, 0, size);

    SDL_Rect bar = {x + strlen(label) * 8 + 4, y, remaped_value, 8};
    SDL_Rect border = {x + strlen(label) * 8 + 4, y, size, 8};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &bar);
    SDL_RenderDrawRect(renderer, &border);
}