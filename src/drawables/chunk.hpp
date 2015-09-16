#ifndef CHUNK_HPP
#define CHUNK_HPP

class Chunk: public Drawable {
  public:
    void draw(float dt);
    void setup();
    Chunk(std::vector<int> data);
    Chunk(std::string path);
    Chunk();
    void setTexture(Texture* texture);
    void setTile(Coordinate tileLocation, int spriteNr);
    void save();
    int width;
    int height;

  private:
    Model model;
    Texture* texture_;
    Program program;
    std::vector<int> data_;

    float position[2];
    
    void generateModel();
};

#endif

