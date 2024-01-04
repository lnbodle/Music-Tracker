#include "phrase_view.h"
#include "../utils/draw_utils.h"
#include "../tracker.h"

void phrase_view(Tracker *tracker, SDL_Renderer *renderer)
{
    set_draw_color(renderer, COLOR_FRONT);

    SDL_Rect note_selection = {PADDING + FONT_WIDTH + (tracker->phrase_mode * FONT_WIDTH * 3), PADDING + tracker->step_index * FONT_HEIGHT, FONT_WIDTH * 3, FONT_HEIGHT};

    set_draw_color(renderer, 0xFF0000);
    SDL_RenderFillRect(renderer, &note_selection);

    int i = tracker->phrase_index;
    for (int j = 0; j < STEP_NUMBER; j++)
    {
        step_draw(&tracker->phrases[i].steps[j], renderer,PADDING + FONT_WIDTH, PADDING + j * FONT_HEIGHT);
    }

    draw_text(renderer, ">", PADDING, PADDING + tracker->phrases[i].step_index * FONT_HEIGHT);

    
}

char NOTES[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

void step_draw(Step *step, SDL_Renderer *renderer, int x, int y)
{
    if (step->note != 0)
    {
        char note_buffer[4];
        sprintf_s(note_buffer, sizeof(note_buffer), "%c-%i", NOTES[step->note - 1], step->octave);
        draw_text(renderer, note_buffer, x, y);
    }
    else
    {
        draw_text(renderer, " - ", x, y);
    }

    char instrument_buffer[2];
    sprintf_s(instrument_buffer, sizeof(instrument_buffer), "%i", step->instrument_id);
    draw_text(renderer, instrument_buffer, x + FONT_WIDTH * 4, y);
}