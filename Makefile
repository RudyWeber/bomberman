all: debug

EXEC_NAME=bomberman

debug:
	gcc -I ./includes src/*.c src/utils/*.c `sdl2-config --cflags --libs` -lSDL2_ttf -lpthread -Wno-initializer-overrides -ggdb -o ${EXEC_NAME}