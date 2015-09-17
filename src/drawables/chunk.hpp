#ifndef CHUNK_HPP
#define CHUNK_HPP

class Chunk: public Drawable {
  public:
    void draw(float dt);
    void setup();
    Chunk(std::string path, Vec2 position);
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

    Vec2 position_;
    
    std::string path_;
    void generateModel();
};

#endif

