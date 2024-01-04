#ifndef TRACKER_H_
#define TRACKER_H_

#include <SDL2/SDL_ttf.h>
#include "audio.h"
#include "event.h"
#include "instrument.h"

#include "../lib/SDL_FontCache/SDL_FontCache.h"

typedef enum {
    INSTRUMENT_ATTACK,
    INSTRUMENT_DECAY,
    INSTRUMENT_SUSTAIN,
    INSTRUMENT_RELEASE,
    INSTRUMENT_WAVEFORM,
    INSTRUMENT_ADSR_PITCH
} InstrumentMode;

typedef enum {

    TRACKER_EDIT_PHRASE,
    TRACKER_EDIT_INSTRUMENT
} TrackerMode;

typedef enum {

    PHRASE_EDIT_NOTE,
    PHRASE_EDIT_INSTRUMENT
} PhraseMode;

typedef struct
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
    Event event;
    Audio audio;
    Phrase phrases[PHRASE_NUMBER];
    Instrument *instruments;

    TrackerMode tracker_mode;
    InstrumentMode instrument_mode;
    PhraseMode phrase_mode;

    size_t instrument_index;
    size_t phrase_index;
    size_t step_index;

    int is_playing;
    int tempo;
} Tracker;

void tracker_init(Tracker *tracker);
void tracker_free(Tracker *tracker);
void tracker_tick(Tracker *tracker, int time);
void tracker_draw(SDL_Renderer *renderer, Tracker *tracker); //TODO : Need to be moved
void tracker_event(Tracker *tracker); //TODO : Need to be moved
void tracker_tick_phrases(Tracker *tracker);

#endif