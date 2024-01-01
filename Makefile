	C_SOURCES = 
	C_SOURCES += \
	src/main.c \
	src/tracker.c \
	src/audio.c \
	src/instrument.c \
	src/utils/draw_utils.c \
	src/utils/audio_utils.c \
	src/utils/math_utils.c \
	src/view/phrase_view.c \
	lib/SDL_inprint/inprint2.c

init :
	gcc -o bin/main -IC:/Dev/soundpipe/h $(C_SOURCES) -lsdl2 -lsdl2_ttf -LC:/Dev/soundpipe -lsoundpipe -lsndfile
	./bin/main.exe
