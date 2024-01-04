#include "../tracker.h"
#include "phrase_event.h"

void phrase_event(Tracker *tracker)
{

    Phrase *phrase = &tracker->phrases[tracker->phrase_index];
    Step *current_step = &phrase->steps[tracker->step_index];

    //Goto Instrument
    if (event_key_down(&tracker->event, Right) && event_key_down(&tracker->event, Action_2))
    {
        tracker->tracker_mode = TRACKER_EDIT_INSTRUMENT; 
        tracker->instrument_index = current_step->instrument_id;
        return;
    }

    // Previous octave
    if (event_key_down(&tracker->event, Down) && event_key_down(&tracker->event, Shift))
    {
        current_step->octave = decrease_index(current_step->octave, 10);
        return;
    }

    // Next octave
    if (event_key_down(&tracker->event, Up) && event_key_down(&tracker->event, Shift))
    {
        current_step->octave = increase_index(current_step->octave, 10);
        return;
    }

    // Next step
    if (event_key_down(&tracker->event, Up))
    {
        tracker->step_index = decrease_index(tracker->step_index, STEP_NUMBER);
        return;
    }

    // Previous step
    if (event_key_down(&tracker->event, Down))
    {
        tracker->step_index = increase_index(tracker->step_index, STEP_NUMBER);
        return;
    }

    // Select Intrument mode
    if (event_key_down(&tracker->event, Right) && event_key_down(&tracker->event, Shift))
    {
        tracker->phrase_mode = PHRASE_EDIT_INSTRUMENT;
        return;
    }

    // Select Intrument mode
    if (event_key_down(&tracker->event, Left) && event_key_down(&tracker->event, Shift))
    {
        tracker->phrase_mode = PHRASE_EDIT_NOTE;
        return;
    }

    // Next note
    if (event_key_down(&tracker->event, Left))
    {
        switch (tracker->phrase_mode)
        {
        case PHRASE_EDIT_INSTRUMENT:
            current_step->instrument_id = decrease_index(current_step->instrument_id, INSTRUMENT_NUMBER);
            break;

        case PHRASE_EDIT_NOTE:
            current_step->note = decrease_index(current_step->note, NOTE_NUMBER);
            break;
        }
        return;
    }

    // Previous note
    if (event_key_down(&tracker->event, Right))
    {
        switch (tracker->phrase_mode)
        {
        case PHRASE_EDIT_INSTRUMENT:
            current_step->instrument_id = increase_index(current_step->instrument_id, INSTRUMENT_NUMBER);
            break;

        case PHRASE_EDIT_NOTE:
            current_step->note = increase_index(current_step->note, NOTE_NUMBER);
            break;
        }
        return;
    }
}