#include <soundpipe.h>
#include "audio.h"

void audio_init(Audio *audio)
{
    SDL_Init(SDL_INIT_AUDIO);

    audio->audio_spec.freq = SAMPLE_RATE;
    audio->audio_spec.format = FORMAT;
    audio->audio_spec.channels = CHANNELS;
    audio->audio_spec.samples = SAMPLES;
    audio->audio_spec.callback = audio_callback;
    audio->audio_spec.userdata = audio;

    audio->audio_device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, 0), 0, &audio->audio_spec, NULL, 0);

    sp_create(&audio->sp);

    sp_bigverb_create(&audio->reverb);
    sp_bigverb_init(audio->sp, audio->reverb);

    for (int i = 0; i < INSTRUMENT_NUMBER; i++)
    {
        instrument_init(&audio->instruments[i], audio->sp);
    }

    SDL_PauseAudioDevice(audio->audio_device, 0);
}

void audio_free(Audio *audio)
{
    SDL_PauseAudioDevice(audio->audio_device, 1);
    for (int i = 0; i < INSTRUMENT_NUMBER; i++)
    {
        instrument_free(&audio->instruments[i]);
    }
    sp_bigverb_destroy(&audio->reverb);
    sp_destroy(&audio->sp);
}

void audio_update(Audio *audio)
{
    for (int i = 0; i < SAMPLES; i++)
    {
        float out = 0;

        for (int n = 0; n < INSTRUMENT_NUMBER; n++)
        {
            out += instrument_process(&audio->instruments[n], audio->sp) / INSTRUMENT_NUMBER;
        }
        float input_0 = 0;

        float reverb_out_0 = 0;
        float reverb_out_1 = 0;

        sp_bigverb_compute(audio->sp, audio->reverb, &out, &input_0, &reverb_out_0, &reverb_out_1);

        audio->buffers[0][i] = out;/*(out * 0.8f + reverb_out_0 * 0.2f)*/;
    }
};

void audio_callback(void *audio, Uint8 *stream, int len)
{
    Audio *a = (Audio *)audio;
    float *buffer = (float *)stream;

    audio_update(a);

    int index;
    for (index = 0; index < len / sizeof(float); index++)
    {
        buffer[index] = a->buffers[0][index];
    }
}
