#ifndef AUDIO_H_
#define AUDIO_H_

#include <SDL2/SDL.h>
#include <soundpipe.h>
#include "instrument.h"
#include "common.h"

#define BUFFERS_NUMBER 4

typedef struct Audio {

    SDL_AudioCallback callback;
    SDL_AudioDeviceID audio_device;
    SDL_AudioSpec audio_spec;

    int buffer_size;
    float buffers[BUFFERS_NUMBER][SAMPLES];

    sp_data *sp;
    sp_bigverb *reverb;
    Instrument instruments[INSTRUMENT_NUMBER];
} Audio;

void audio_init(Audio *audio);
void audio_free(Audio *audio);
void audio_update(Audio *audio);
void audio_callback(void *audio, Uint8 *stream, int len);

#endif