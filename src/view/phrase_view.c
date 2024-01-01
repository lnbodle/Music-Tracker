#include "phrase_view.h"
#include "../utils/draw_utils.h"
#include "../tracker.h"

void phrase_view(Tracker *tracker, SDL_Renderer *renderer)
{
    for (int i = 0; i < PHRASE_NUMBER; i++)
    {
        for (int j = 0; j < STEP_NUMBER; j++)
        {
            step_draw(&tracker->phrases[i].steps[j], renderer, i * 32, j * 8);
        }
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect note_selection = {i * 32, tracker->phrases[i].step_index * 8, 16, 8};
        SDL_RenderDrawRect(renderer, &note_selection);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect note_selection = {tracker->phrase_index * 32, tracker->step_index * 8, 16, 8};
    SDL_RenderDrawRect(renderer, &note_selection);

    SDL_Rect phrase_selection = {tracker->phrase_index * 32, 0, 32, 8 * STEP_NUMBER};
    SDL_RenderDrawRect(renderer, &phrase_selection);
}

char NOTES[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

void step_draw(Step *step, SDL_Renderer *renderer, int x, int y)
{
    if (step->note != 0)
    {
        char note_buffer[3];
        sprintf_s(note_buffer, sizeof(note_buffer), "%c%i", NOTES[step->note - 1], step->octave);
        draw_text(renderer, note_buffer, x, y);
    }
    else
    {
        draw_text(renderer, "--", x, y);
    }

    char instrument_buffer[2];
    sprintf_s(instrument_buffer, sizeof(instrument_buffer), "%i", step->instrument_id);
    draw_text(renderer, instrument_buffer, x + 16, y);
}