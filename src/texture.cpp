#include "config.hpp"

Texture::Texture(const char* filepath){
  filepath_ = filepath;

  load();
}

GLuint Texture::getID(){
  return textureID_;
}

void Texture::load(){
  printf("Loading texture ...");
  std::vector<unsigned char> buffer, image;
  lodepng::load_file(buffer, filepath_); //load the image file with given filename
  unsigned w, h;
  unsigned error = lodepng::decode(image, w, h, buffer); //decode the png
  dimensions[0] = w;
  dimensions[0] = h;

  glGenTextures(1, &textureID_);
  glBindTexture(GL_TEXTURE_2D, textureID_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
  printf("done\n");
}


