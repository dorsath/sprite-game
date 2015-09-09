#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
  public:
    int dimensions[2];
    Texture(const char* filepath);
    GLuint getID();

  private:
    const char* filepath_;
    void load();
    GLuint textureID_;

};

#endif


