#include <soundpipe.h>
#include "common.h"
#include "instrument.h"

void instrument_init(Instrument *instrument, sp_data *sp) {

    instrument->waveshape = SAW;
    instrument->frequency = 440.0f;

    sp_adsr_create(&instrument->adsr);
    sp_adsr_init(sp, instrument->adsr);

    /*sp_osc_create(&instrument->osc);
    sp_ftbl_create(sp, &instrument->ft, SAMPLES);*/

    //Square
    sp_blsquare_create(&instrument->square);
    sp_blsquare_init(sp, instrument->square);

    //Saw
    sp_blsaw_create(&instrument->saw);
    sp_blsaw_init(sp, instrument->saw);

    //Lowpass 
    sp_butlp_create(&instrument->filter);
    sp_butlp_init(sp, instrument->filter);
    



    /*sp_gen_triangle(sp, instrument->ft);
    sp_osc_init(sp, instrument->osc, instrument->ft, 0);*/

    instrument->adsr->atk = 0;
    instrument->gate = 0;
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
    /*sp_ftbl_destroy(&instrument->ft);
    sp_osc_destroy(&instrument->osc);*/

    sp_blsaw_destroy(&instrument->saw);
    sp_blsquare_destroy(&instrument->square);

    sp_butlp_destroy(&instrument->filter);
}

float instrument_process(Instrument *instrument, sp_data *sp) {

    //instrument->osc->freq = instrument->frequency;

    SPFLOAT osc = 0, adsr = 0;

    sp_adsr_compute(sp, instrument->adsr, &instrument->gate, &adsr);

    float pitch = (float)instrument->frequency + (adsr * instrument->adsr_pitch);

    switch(instrument->waveshape) {
        case SAW: 
            *instrument->saw->freq = pitch;
            sp_blsaw_compute(sp, instrument->saw, NULL, &osc);
        break;
        case SQUARE:
            *instrument->square->freq = pitch;
            sp_blsquare_compute(sp, instrument->square, NULL, &osc);
        break;
    }

    instrument->filter->lfreq = adsr;

    sp_butlp_compute(sp, instrument->filter, &osc, &osc);

    instrument->gate = 0;

    return adsr * osc;
}