#include "config.hpp"

std::string Texture::folder = "./textures/";
std::vector<Texture*> Texture::loadedTextures_;

GLuint Texture::getID(){
  return textureID_;
}

Texture::Texture(){}

Texture::Texture(std::string filename){
  load(filename);
}

void Texture::load(std::string filename_in){
  filename = filename_in;

  std::stringstream fmt; 
  fmt << folder << filename;

  std::cout << "Loading texture ...";
  std::vector<unsigned char> buffer, image;
  lodepng::load_file(buffer, fmt.str()); //load the image file with given filename
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
  std::cout << "done" << std::endl;

  Texture::loadedTextures_.push_back(this);
}

Texture* Texture::find_or_create(std::string filename_in){
  for(Texture* texture: loadedTextures_){
    if (texture->filename == filename_in) {
      std::cout << "reusing texture" << filename_in <<  std::endl;
      return texture;
    }
  }

  std::cout << "Building new texture: " << filename_in << std::endl;

  Texture* newTexture = new Texture(filename_in);
  return newTexture;
}


