#ifndef DRAWABLES_LEVEL_HPP
#define DRAWABLES_LEVEL_HPP

class Level: public Drawable {
  public:
    Level(std::string file);
    void draw(float dt);
    void setup();
    void setTexture(Texture* texture);
    void save();
    void load();

  private:
    struct ChunkData {
      int x;
      int y;
      int n;
    };

    std::vector<Chunk*> chunks;

    std::string filename_;
    std::vector<ChunkData> data_;
    Texture* texture_;

    
};

#endif




