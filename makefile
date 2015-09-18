CC=c++
FLAGS=-std=c++11 -Wc++11-extensions `pkg-config --cflags glfw3 --libs glfw3` -framework OpenGL
DEBS=src/display.o src/program.o src/model.o src/fbo.o lib/Matrices.o src/font.o lib/lodepng.o src/texture.o src/vector.o src/timeout.o
DEBS+=src/drawables/sprite.o src/drawables/chunk.o src/drawables/text.o src/drawables/item.o src/drawables/player.o src/drawables/builder.o src/drawables/fps_meter.o src/drawables/level.o

all: $(DEBS)
	$(CC) $(FLAGS) -o bin/main src/main.cpp $(DEBS)
	./bin/main

ss: $(DEBS)
	$(CC) $(FLAGS) -o bin/sprite_selector src/sprite_selector.cpp $(DEBS)
	./bin/sprite_selector

cb: $(DEBS)
	$(CC) $(FLAGS) -o bin/chunk_builder src/chunk_builder.cpp $(DEBS)
	./bin/chunk_builder


