#include "../utils/draw_utils.h"
#include "instrument_view.h"
#include "../tracker.h"

char waveform[2][10] = {"SAW", "SQUARE"};

void instrument_view(Tracker *tracker, SDL_Renderer *renderer)
{
    Instrument *instrument = &tracker->audio.instruments[tracker->instrument_index];

    char instrument_index_buffer[20];
    sprintf_s(instrument_index_buffer, sizeof(instrument_index_buffer), "INSTRUMENT %i", tracker->instrument_index);
    draw_text(renderer, instrument_index_buffer, PADDING, PADDING);

    set_draw_color(renderer, 0xFF0000);
    SDL_Rect selection = {PADDING  , PADDING + 16 + FONT_HEIGHT + (tracker->instrument_mode * FONT_HEIGHT), FONT_WIDTH * 12, FONT_HEIGHT};
    SDL_RenderFillRect(renderer, &selection);

    draw_slider(renderer, "Attack", PADDING, PADDING + 16 + FONT_HEIGHT, 64, instrument->adsr->atk, 0, 1);
    draw_slider(renderer, "Decay", PADDING, PADDING + 16 + FONT_HEIGHT * 2, 64, instrument->adsr->dec, 0, 1);
    draw_slider(renderer, "Sustain", PADDING, PADDING + 16 + FONT_HEIGHT * 3, 64, instrument->adsr->sus, 0, 1);
    draw_slider(renderer, "Release", PADDING, PADDING + 16 + FONT_HEIGHT * 4, 64, instrument->adsr->rel, 0, 1);

    draw_text(renderer, "Waveform", PADDING,  PADDING + 16 + FONT_HEIGHT * 5);
    draw_text(renderer, waveform[instrument->waveshape], PADDING + FONT_WIDTH * 12,  PADDING + 16 + FONT_HEIGHT * 5);

    draw_slider(renderer, "Pitch Env", PADDING,  PADDING + 16 + FONT_HEIGHT * 6, 64, instrument->adsr_pitch, 0, 200);
}