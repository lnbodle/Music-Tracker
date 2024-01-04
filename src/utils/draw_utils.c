#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "math_utils.h"
#include "../../lib/SDL_inprint/SDL2_inprint.h"
#include "../common.h"

#include "../../lib/SDL_FontCache/SDL_FontCache.h"

FC_Font *fc_font;

TTF_Font *ttf_font;

void set_draw_color(SDL_Renderer *renderer, Uint32 color)
{

    int r = (color >> 16) & 0xff; // red
    int g = (color >> 8) & 0xff;  // green
    int b = color & 0xff;         // blue
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    incolor(color, 0);
}

void init_font(SDL_Renderer *renderer)
{
    

    if (TTF_Init() != 0)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    fc_font = FC_CreateFont();
    SDL_Color color = {227,211,171, 255};

    ttf_font = TTF_OpenFont("./assets/Iosvmata-Regular.ttf", FONT_HEIGHT);
    if (ttf_font == NULL)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(2);
    }

    FC_LoadFontFromTTF(fc_font, renderer, ttf_font, color);

}

void close_font()
{
    FC_FreeFont(fc_font);
}

void draw_text(SDL_Renderer *renderer, char *text, int x, int y)
{
    // inprint(renderer, text, x, y);
    FC_Draw(fc_font, renderer, x, y, text);
}

void draw_wave_form(SDL_Renderer *renderer, SDL_Rect *bounds, float *buffer, int buffer_size)
{
    set_draw_color(renderer, COLOR_FRONT);
    for (int i = 0; i < bounds->w; i++)
    {
        int remaped_index = (buffer_size / bounds->w) * i;

        int middle = bounds->y + (bounds->h / 2);
        float range = buffer[remaped_index] * (bounds->h * 2);

        SDL_RenderDrawPoint(renderer, bounds->x + i, middle + range);
    }
}

void draw_slider(SDL_Renderer *renderer, char *label, int x, int y, int size, float value, float min, float max)
{
    set_draw_color(renderer, COLOR_FRONT);

    draw_text(renderer, label, x, y);

    if (value > max)
        value = max;
    if (value < min)
        value = min;

    int remaped_value = remap(value, min, max, 0, size);

    int max_char = 12;

    SDL_Rect bar = {x + max_char * FONT_WIDTH, y, remaped_value, FONT_HEIGHT};
    SDL_Rect border = {x + max_char * FONT_WIDTH, y, size, FONT_HEIGHT};

    SDL_RenderFillRect(renderer, &bar);
    SDL_RenderDrawRect(renderer, &border);
}