#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include "../lib/SDL_inprint/SDL2_inprint.h"
#include "utils/draw_utils.h"
#include "tracker.h"
#include "common.h"

#include "../lib/SDL_FontCache/SDL_FontCache.h"

Tracker tracker;

	
//FC_Font* font;

SDL_TimerID tick_id;
int time = 0;
SDL_TimerCallback tick(Uint32 interval, void *param)
{
    int *a = (int *)param;
    tracker_tick(&tracker, time);
    time++;
    return 1;
}

int states[6];

void init()
{
    tracker_init(&tracker);
}

void draw(SDL_Renderer *renderer)
{
   tracker_draw(renderer, &tracker);
}

int main(int argc, char *argv[])
{
    int sdl_init = SDL_Init(SDL_INIT_EVERYTHING);
    if (sdl_init)
    {
        printf("SDL can't be initalize");
        return 1;
    }

    SDL_AddTimer(1, tick, time);

    SDL_Window *window = SDL_CreateWindow("TRACKER", 128, 128, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL)
    {
        printf("SDL_Window can't be initalize");
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0 /* SDL_RENDERER_TARGETTEXTURE*/);
    if (renderer == NULL)
    {
        printf("SDL_Render can't be initalize");
        return 1;
    }

    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    	
    inrenderer(renderer);
    prepare_inline_font();

    /*SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderSetIntegerScale(renderer, 1);*/

    int quit = 0;
    SDL_Event e;

    init();

    init_font(renderer);

    while (!quit)
    {
        SDL_RenderClear(renderer);
        set_draw_color(renderer, COLOR_BACK);
        SDL_RenderFillRect(renderer, NULL);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        draw(renderer);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }

            if (e.type == SDL_KEYDOWN)
            {

                SDL_Keycode code = e.key.keysym.sym;

                event_set_states(&tracker.event, code, 1);
                tracker_event(&tracker);
            }

            if (e.type == SDL_KEYUP)
            {
                SDL_Keycode code = e.key.keysym.sym;
                event_set_states(&tracker.event, code, 0);
            }
        }
    }

    tracker_free(&tracker);
    //kill_inline_font();

    close_font();
    //TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
