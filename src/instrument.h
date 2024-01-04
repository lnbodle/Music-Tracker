#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

#include <soundpipe.h>

typedef enum {
    SAW,
    SQUARE
} Waveshape;

typedef struct
{
    sp_adsr *adsr;
    /*sp_osc *osc;
    sp_ftbl *ft;*/

    sp_butlp *filter;

    sp_blsquare *square;
    sp_blsaw *saw;
    sp_bltriangle *triangle;

    Waveshape waveshape;
    float gate;
    float frequency;

    float adsr_pitch;
} Instrument;

void instrument_init(Instrument *instrument, sp_data *sp);
void instrument_free(Instrument *instrument);
void instrument_on(Instrument *instrument, float frequency);
void instrument_off(Instrument *instrument);
float instrument_process(Instrument *instrument, sp_data *sp);

#endif