#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <stdio.h>
#include "tracker.h"
#include "common.h"

Tracker tracker;

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

    SDL_Window *window = SDL_CreateWindow("TRACKER", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
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

    inrenderer(renderer);
    prepare_inline_font();

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderSetIntegerScale(renderer, 1);

    int quit = 0;
    SDL_Event e;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    init();

    while (!quit)
    {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
                
                switch (code)
                {
                case SDLK_LEFT:
                    states[Left] = 1;
                    break;
                case SDLK_RIGHT:
                    states[Right] = 1;
                    break;
                case SDLK_UP:
                    states[Up] = 1;
                    break;
                case SDLK_DOWN:
                    states[Down] = 1;
                    break;
                case SDLK_LSHIFT:
                    states[Shift] = 1;
                    break;
                case SDLK_SPACE:
                    states[Action_1] = 1;
                    break;
                case SDLK_a:
                    states[Action_2] = 1;
                default:
                    break;
                }
                tracker_event(&tracker, &states);
            }

            if (e.type == SDL_KEYUP)
            {
                SDL_Keycode code = e.key.keysym.sym;
                switch (code)
                {
                case SDLK_LEFT:
                    states[Left] = 0;
                    break;
                case SDLK_RIGHT:
                    states[Right] = 0;
                    break;
                case SDLK_UP:
                    states[Up] = 0;
                    break;
                case SDLK_DOWN:
                    states[Down] = 0;
                    break;
                case SDLK_LSHIFT:
                    states[Shift] = 0;
                    break;
                case SDLK_SPACE:
                    states[Action_1] = 0;
                    break;
                case SDLK_a:
                    states[Action_2] = 0;
                    break;
                default:
                    break;
                }
            }
            
        }
    }

    tracker_free(&tracker);
    kill_inline_font();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
