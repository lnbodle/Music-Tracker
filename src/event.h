#include <SDL2/SDL.h>

typedef enum
{
    Up,
    Down,
    Left,
    Right,
    Shift,
    Action_1,
    Action_2
} EventType;

typedef struct
{
    EventType states[6];
} Event;

int event_key_down(Event *event, EventType event_type);
void event_set_states(Event *event, SDL_Keycode code, int value);