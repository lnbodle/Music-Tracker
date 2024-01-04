#ifndef COMMON_H_
#define COMMON_H_

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

#define COLOR_FRONT 0xE7751C
#define COLOR_BACK  0x171717

#define FONT_WIDTH 9
#define FONT_HEIGHT 16
#define PADDING 8

#endif