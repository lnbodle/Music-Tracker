#include "../tracker.h"
#include "../utils/math_utils.h"
#include "instrument_event.h"

void instrument_event(Tracker *tracker)
{
    Instrument *instrument = &tracker->audio.instruments[tracker->instrument_index];

    //tracker->instrument_mode = INSTRUMENT_ATTACK;

    if (event_key_down(&tracker->event, Left) && event_key_down(&tracker->event, Action_2))
    {
        tracker->tracker_mode = TRACKER_EDIT_PHRASE;
    }

    if (event_key_down(&tracker->event, Down))
    {
        //tracker->instrument_mode ++;
        tracker->instrument_mode = increase_index(tracker->instrument_mode, 6);
    }

    if (event_key_down(&tracker->event, Up))
    {
        //tracker->instrument_mode --;
        tracker->instrument_mode = decrease_index(tracker->instrument_mode, 6);
    }

    if (event_key_down(&tracker->event, Right))
    {
        switch (tracker->instrument_mode)
        {
        case INSTRUMENT_ATTACK:
            instrument->adsr->atk += 0.1f;
            break;
        case INSTRUMENT_SUSTAIN:
            instrument->adsr->sus += 0.1f;
            break;
        case INSTRUMENT_DECAY:
            instrument->adsr->dec += 0.1f;
            break;
        case INSTRUMENT_RELEASE:
            instrument->adsr->rel += 0.1f;
            break;
        case INSTRUMENT_WAVEFORM:
            instrument->waveshape = increase_index(instrument->waveshape, 2);
            break;
        case INSTRUMENT_ADSR_PITCH:
            instrument->adsr_pitch += 5;
            break;
        }
    }

    if (event_key_down(&tracker->event, Left))
    {
        switch (tracker->instrument_mode)
        {
        case INSTRUMENT_ATTACK:
            instrument->adsr->atk -= 0.1f;
            break;
        case INSTRUMENT_SUSTAIN:
            instrument->adsr->sus -= 0.1f;
            break;
        case INSTRUMENT_DECAY:
            instrument->adsr->dec -= 0.1f;
            break;
        case INSTRUMENT_RELEASE:
            instrument->adsr->rel -= 0.1f;
            break;
        case INSTRUMENT_WAVEFORM:
            instrument->waveshape = decrease_index(instrument->waveshape,  2);
            break;
        case INSTRUMENT_ADSR_PITCH:
            instrument->adsr_pitch -= 5;
            break;
        }      
    }
}