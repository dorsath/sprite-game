#include "/Users/ronald/Projects/cpp/octree/src/octree.hpp"
#include <fstream>

Octree ct_to_octree(const char* path, int resolution, int z_offset = 84){
  Octree octree;
  octree.resolution = resolution;

  const char* filepath = "./textures/ct.raw";

  short int buffer;
  FILE* file = fopen(filepath, "rb");

  fseek(file, 0L, SEEK_END);
  int size = ftell(file) / sizeof(buffer);
  fseek(file, 0L, SEEK_SET);
  printf("size:%d\n", size);

  int x = 0;
  int y = 0;
  int z = z_offset;

  for (int i = 0; i < size; i += 1){
    fread((void*)(&buffer), sizeof(buffer), 1, file);
    if (buffer > 300 && y < 340){
      float value = log(float(buffer)) / 8.0;
      float color[4] = {value, value, value, 1.0};
      octree.set(x,y,z,color);
      octree.set(x,y, z + 1,color);
    }

    x += 1;
    if (x > 511){
      x = 0;
      y += 1;
    }
    if (y > 511){
      y = 0;
      z += 2;
    }
    
    //printf("buffer: %d\n", buffer);

  }

  fclose(file);

  return octree;
}
