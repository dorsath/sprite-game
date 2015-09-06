#include "config.hpp"

void Octree::load(const char* filepath, int set_resolution){
  resolution = set_resolution;
  display::check_error("Error before loading octree");
  printf("Loading octree:%s...", filepath);
  FILE* file;
  float buffer;

  file = fopen(filepath, "rb");
  fseek(file, 0L, SEEK_END);

  int sz = ftell(file) / 16;
  for (length = 1; length * length < sz; length = length << 1);
  int size = length*length * 4;
  float* volumeData = new float[size];
  
  fseek(file, 0L, SEEK_SET);
  for (int i = 0; i < size; i += 1){
    fread((void*)(&volumeData[i]), sizeof(buffer), 1, file);
  }
  fclose(file);

  printf("done\n");

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, length, length, 0, GL_RGBA, GL_FLOAT, volumeData);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


  delete volumeData;
  
  
  display::check_error("Error after loading octree");
}
