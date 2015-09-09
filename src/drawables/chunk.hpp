#ifndef CHUNK_HPP
#define CHUNK_HPP

class Chunk: public Drawable {
  public:
    void draw();
    void setup();
    Chunk();

  private:
    int width;
    int height;
    Model model;
    GLuint textureID;
    Program program;
    
    void generateTexture();
    void generateModel();
};

#endif

