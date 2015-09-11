#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
  public:
    int dimensions[2];
    void load(const char* filepath);
    GLuint getID();

  private:
    const char* filepath_;
    GLuint textureID_;

};

#endif


