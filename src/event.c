#include "event.h"

int event_key_down(Event *event, EventType event_type) {
    return event->states[event_type];
}

void event_set_states(Event *event, SDL_Keycode code, int value)
{
    switch (code)
    {
    case SDLK_LEFT:
        event->states[Left] = value;
        break;
    case SDLK_RIGHT:
        event->states[Right] = value;
        break;
    case SDLK_UP:
        event->states[Up] = value;
        break;
    case SDLK_DOWN:
        event->states[Down] = value;
        break;
    case SDLK_LSHIFT:
        event->states[Shift] = value;
        break;
    case SDLK_SPACE:
        event->states[Action_1] = value;
        break;
    case SDLK_a:
        event->states[Action_2] = value;
    default:
        break;
    }
}