#include "config.hpp"




void Font::setup(){

  const char* filepath = "textures/font.png";
  std::vector<unsigned char> buffer, image;
  lodepng::load_file(buffer, filepath); //load the image file with given filename
  unsigned w, h;
  unsigned error = lodepng::decode(image, w, h, buffer); //decode the png

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
}
