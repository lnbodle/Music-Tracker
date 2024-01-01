#ifndef TRACKER_H_
#define TRACKER_H_

#include <SDL2/SDL_ttf.h>
#include "audio.h"
#include "instrument.h"

typedef enum TrackerModes {

    MODE_EDIT_TRACKER,
    MODE_EDIT_PHRASE,
    MODE_EDIT_INSTRUMENT
} EditMode;

typedef struct Step
{
    int note;
    int octave;
    int instrument_id;
} Step;

typedef struct
{
    Step steps[STEP_NUMBER];
    size_t step_index;
} Phrase;

typedef struct Tracker
{
    Audio audio;
    Phrase phrases[PHRASE_NUMBER];
    Instrument *instruments;
    EditMode edit_mode;
    size_t phrase_index;
    size_t step_index;
    int is_playing;
    int tempo;
} Tracker;

void tracker_init(Tracker *tracker);
void tracker_free(Tracker *tracker);
void tracker_tick(Tracker *tracker, int time);
void tracker_draw(SDL_Renderer *renderer, Tracker *tracker); //TODO : Need to be moved
void tracker_event(Tracker *tracker, int *states); //TODO : Need to be moved
void tracker_tick_phrases(Tracker *tracker);

#endif