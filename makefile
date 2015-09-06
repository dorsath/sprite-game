CC=c++
FLAGS=-std=c++0x -Wc++11-extensions `pkg-config --cflags glfw3 --libs glfw3` -framework OpenGL
DEBS=src/display.o src/program.o src/model.o src/background.o src/fbo.o src/object.o lib/Matrices.o src/slice.o src/octree.o src/polygon.o src/text.o src/font.o lib/lodepng.o

all: $(DEBS)
	$(CC) $(FLAGS) -o bin/main src/main.cpp $(DEBS)
	./bin/main


objects:
	c++ -o objects lib/objects.cpp
	./objects
	rm ./objects

octree:
	c++ -o objects lib/create_objects.cpp
	./objects
	rm ./objects

CT_DEBS=~/Projects/cpp/octree/src/octree.o

ct_to_octree: $(CT_DEBS)
	c++ $(CT_DEBS) -o ct_to_octree lib/ct_to_octree.cpp
	./ct_to_octree
	rm ./ct_to_octree

octree_to_polygon: $(CT_DEBS)
	c++ $(CT_DEBS) -o octree_to_polygon lib/octree_to_polygon.cpp
	./octree_to_polygon
	rm ./octree_to_polygon

