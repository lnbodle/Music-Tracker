#ifndef PHRASE_VIEW_H_
#define PHRASE_VIEW_H_

#include "../tracker.h";

void phrase_view(Tracker *tracker, SDL_Renderer *renderer);
void step_draw(Step *step, SDL_Renderer *renderer, int x, int y);

#endif