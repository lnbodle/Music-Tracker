#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

#include <soundpipe.h>

typedef struct
{
    sp_adsr *adsr;
    sp_osc *osc;
    sp_ftbl *ft;
    float gate;
    float frequency;
} Instrument;

void instrument_init(Instrument *instrument, sp_data *sp);
void instrument_free(Instrument *instrument);
void instrument_on(Instrument *instrument, float frequency);
void instrument_off(Instrument *instrument);
float instrument_process(Instrument *instrument, sp_data *sp);

#endif