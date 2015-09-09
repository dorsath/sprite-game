CC=c++
FLAGS=-std=c++0x -Wc++11-extensions `pkg-config --cflags glfw3 --libs glfw3` -framework OpenGL
DEBS=src/display.o src/program.o src/model.o src/fbo.o lib/Matrices.o src/text.o src/font.o lib/lodepng.o src/sprite.o src/chunk.o

all: $(DEBS)
	$(CC) $(FLAGS) -o bin/main src/main.cpp $(DEBS)
	./bin/main

ss: $(DEBS)
	$(CC) $(FLAGS) -o bin/sprite_selector src/sprite_selector.cpp $(DEBS)
	./bin/sprite_selector

