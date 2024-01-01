#include <soundpipe.h>
#include "common.h"
#include "instrument.h"

void instrument_init(Instrument *instrument, sp_data *sp) {

    sp_adsr_create(&instrument->adsr);
    sp_osc_create(&instrument->osc);
    sp_ftbl_create(sp, &instrument->ft, SAMPLES);

    sp_adsr_init(sp, instrument->adsr);
    sp_gen_triangle(sp, instrument->ft);
    sp_osc_init(sp, instrument->osc, instrument->ft, 0);

    instrument->adsr->atk = 0;
}

void instrument_on(Instrument *instrument, float frequency) {

    instrument->frequency = frequency;
    instrument->gate = 1;
}

void instrument_off(Instrument *instrument) {

    instrument->gate = 0;
}

void instrument_free(Instrument *instrument) {

    sp_adsr_destroy(&instrument->adsr);
    sp_ftbl_destroy(&instrument->ft);
    sp_osc_destroy(&instrument->osc);
}

float instrument_process(Instrument *instrument, sp_data *sp) {

    instrument->osc->freq = instrument->frequency;

    SPFLOAT osc = 0, adsr = 0;

    sp_adsr_compute(sp, instrument->adsr, &instrument->gate, &adsr);
    sp_osc_compute(sp, instrument->osc, NULL, &osc);

    return adsr * osc;
}