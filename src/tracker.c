#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "audio.h"
#include "tracker.h"
#include "utils/draw_utils.h"
#include "utils/audio_utils.h"
#include "instrument.h"
#include "common.h"
#include "view/phrase_view.h"

void tracker_init(Tracker *tracker)
{

    tracker->phrase_index = 0;
    tracker->step_index = 0;

    tracker->edit_mode = MODE_EDIT_TRACKER;
    tracker->is_playing = 0;

    audio_init(&tracker->audio);

    for (int i = 0; i < PHRASE_NUMBER; i++)
    {
        tracker->phrases[i].step_index = 0;

        for (int j = 0; j < STEP_NUMBER; j++)
        {
            tracker->phrases[i].steps[j].note = 0;
            tracker->phrases[i].steps[j].octave = 4;
            tracker->phrases[i].steps[j].instrument_id = i;
        }
    }
}

void tracker_free(Tracker *tracker)
{

    audio_free(&tracker->audio);
}

void tracker_next(Tracker *tracker)
{
    tracker->phrase_index++;
    if (tracker->phrase_index > PHRASE_NUMBER - 1)
        tracker->phrase_index = 0;
}

void tracker_previous(Tracker *tracker)
{
}

void tracker_draw(SDL_Renderer *renderer, Tracker *tracker)
{
    SDL_Rect rect = {0, SCREEN_WIDTH - 64, SCREEN_WIDTH, 64};
    draw_wave_form(renderer, &rect, &tracker->audio.buffers[0], 512);

    char *mode;
    switch (tracker->edit_mode)
    {
    case MODE_EDIT_TRACKER:
        mode = "TRACKER";
        break;
    case MODE_EDIT_PHRASE:
        mode = "PHRASE";
        break;
    case MODE_EDIT_INSTRUMENT:
        mode = "INSTRUMENT";
    }
    draw_text(renderer, mode, SCREEN_WIDTH - strlen(mode) * 8, 0);

    char *playing;
    if (tracker->is_playing) {
        playing = ">";
    } else {
        playing = "||";
    }
    draw_text(renderer, playing, SCREEN_WIDTH - strlen(playing) * 8, 8);

    phrase_view(tracker, renderer);
}

void tracker_tick(Tracker *tracker, int time)
{
    if (tracker->is_playing)
    {
        if (time % 100 == 0)
        {
            tracker_tick_phrases(tracker);
        }
    }
}

void tracker_tick_phrases(Tracker *tracker)
{
    for (int i = 0; i < PHRASE_NUMBER; i++)
    {
        Phrase *phrase = &tracker->phrases[i];
        Step *current_step = &phrase->steps[phrase->step_index];

        instrument_off(&tracker->audio.instruments[current_step->instrument_id]);

        if (current_step->note != 0)
        {
            float frequency = freq(current_step->note, ' ', current_step->octave);
            instrument_on(&tracker->audio.instruments[current_step->instrument_id], frequency);
        }

        phrase->step_index++;
        if (phrase->step_index >= STEP_NUMBER)
        {
            phrase->step_index = 0;
        }
        
    }
}

void tracker_reset_phrases(Tracker *tracker)
{
    for (int i = 0; i < PHRASE_NUMBER; i++)
    {
        tracker->phrases[i].step_index = 0;
    }
}

void tracker_event(Tracker *tracker, int *states)
{

    Phrase *phrase = &tracker->phrases[tracker->phrase_index];
    Step *current_step = &phrase->steps[tracker->step_index];

    switch (tracker->edit_mode)
    {

    case MODE_EDIT_TRACKER:

        if (states[Action_1])
        {

            if (states[Shift])
            {
                tracker->edit_mode = MODE_EDIT_PHRASE;
            }
            else
            {
                tracker->is_playing = !tracker->is_playing;
                tracker_reset_phrases(tracker);
            }
        }

        if (states[Right])
        {
            tracker->phrase_index++;
            if (tracker->phrase_index >= PHRASE_NUMBER)
                tracker->phrase_index = 0;
        }

        break;

    case MODE_EDIT_PHRASE:

        if (states[Shift] && states[Action_1])
        {
            tracker->edit_mode = MODE_EDIT_TRACKER;
        }

        if (states[Down])
        {
            tracker->step_index++;
            if (tracker->step_index > STEP_NUMBER)
                tracker->step_index = 0;
        }

        if (states[Up])
        {
            tracker->step_index--;
            if (tracker->step_index < 0)
                tracker->step_index = STEP_NUMBER;
        }

        if (states[Right])
        {

            if (states[Shift])
            {
                current_step->octave--;
            }
            else
            {
                current_step->note--;
            }
        }

        if (states[Left])
        {
            if (states[Shift])
            {
                current_step->octave++;
            }
            else
            {
                current_step->note++;
            }
        }

        break;

    default:

        break;
    }
}