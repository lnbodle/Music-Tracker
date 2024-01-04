#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "audio.h"
#include "tracker.h"
#include "utils/draw_utils.h"
#include "utils/audio_utils.h"
#include "utils/math_utils.h"
#include "instrument.h"
#include "common.h"
#include "view/phrase_view.h"
#include "view/instrument_view.h"
#include "event/phrase_event.h"
#include "event/instrument_event.h"

void tracker_init(Tracker *tracker)
{
    tracker->tempo = 480;
    tracker->phrase_index = 0;
    tracker->step_index = 0;

    tracker->tracker_mode = TRACKER_EDIT_PHRASE;
    tracker->instrument_mode = INSTRUMENT_ATTACK;
    tracker->phrase_mode = PHRASE_EDIT_NOTE; // maybe be in phrase but seems useless ?

    tracker->is_playing = 0;

    audio_init(&tracker->audio);

    for (int i = 0; i < PHRASE_NUMBER; i++)
    {
        tracker->phrases[i].step_index = 0;

        for (int j = 0; j < STEP_NUMBER; j++)
        {
            tracker->phrases[i].steps[j].note = 0;
            tracker->phrases[i].steps[j].octave = 5;
            tracker->phrases[i].steps[j].instrument_id = i;
        }
    }
}

void tracker_free(Tracker *tracker)
{
    audio_free(&tracker->audio);
}

void tracker_draw(SDL_Renderer *renderer, Tracker *tracker)
{
    SDL_Rect rect = {0, SCREEN_HEIGHT - 48, SCREEN_WIDTH, 48};
    draw_wave_form(renderer, &rect, &tracker->audio.buffers[0], 512);
    
    switch (tracker->tracker_mode)
    {
    case TRACKER_EDIT_PHRASE:
        phrase_view(tracker, renderer);
        break;

    case TRACKER_EDIT_INSTRUMENT:
        instrument_view(tracker, renderer);
        break;

    default:
        break;
    }
}

void tracker_tick(Tracker *tracker, int time)
{
    if (tracker->is_playing)
    {
        if (time % (1000 * 60 / tracker->tempo) == 0)
        {
            tracker_tick_phrases(tracker);
        }
    }
}

void tracker_tick_phrases(Tracker *tracker)
{
    Phrase *phrase = &tracker->phrases[tracker->phrase_index];
    Step *current_step = &phrase->steps[phrase->step_index];

    if (current_step->note != 0)
    {
        float frequency = freq(current_step->note, ' ', current_step->octave);
        instrument_on(&tracker->audio.instruments[current_step->instrument_id], frequency);
    }

    phrase->step_index = increase_index(phrase->step_index, STEP_NUMBER);
}

void tracker_reset_phrases(Tracker *tracker)
{
    for (int i = 0; i < PHRASE_NUMBER; i++)
    {
        tracker->phrases[i].step_index = 0;
    }
}

void tracker_event(Tracker *tracker)
{
    if (event_key_down(&tracker->event, Action_1))
    {
        tracker->is_playing = !tracker->is_playing;
        tracker_reset_phrases(tracker);
    }

    switch (tracker->tracker_mode)
    {
    case TRACKER_EDIT_PHRASE:
        phrase_event(tracker);
        break;
    case TRACKER_EDIT_INSTRUMENT:
        instrument_event(tracker);
        break;

    default:
        break;
    }
}