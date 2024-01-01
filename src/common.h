#ifndef COMMON_H_
#define COMMON_H_

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define AUDIO_DEVICE 0
#define CHANNELS 1
#define FORMAT AUDIO_F32
#define SAMPLE_RATE 48000
#define SAMPLES 1024

#define STEP_NUMBER 16
#define CHAIN_NUMBER 16
#define PHRASE_NUMBER 4
#define INSTRUMENT_NUMBER 4
#define NOTE_NUMBER 8

enum {
    Up,
    Down,
    Left,
    Right,
    Shift,
    Action_1,
    Action_2
};

#endif