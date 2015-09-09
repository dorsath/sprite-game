#ifndef CHUNK_HPP
#define CHUNK_HPP

class Chunk: public Drawable {
  public:
    void draw();
    void setup();
    Chunk(std::vector<int> data);

  private:
    int width;
    int height;
    Model model;
    GLuint textureID;
    Program program;
    std::vector<int> data_;

    float position[2];
    
    void generateTexture();
    void generateModel();
};

#endif

