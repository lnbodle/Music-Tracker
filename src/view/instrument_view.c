#include "../utils/draw_utils.h"
#include "../tracker.h"

void instrument_view(Tracker *tracker, SDL_Renderer *renderer) {

    //Attack 
    draw_slider(renderer, "Attack", 0, 0, 64, 10,0,30);
}