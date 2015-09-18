#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
  public:
    int dimensions[2];
    void load(std::string filename_in);
    std::string filename;
    GLuint getID();

    Texture(std::string filename_in);
    Texture();

    static Texture* find_or_create(std::string filename_in);
    static std::string folder;

  private:
    GLuint textureID_;
    static std::vector<Texture*> loadedTextures_;

};

#endif


