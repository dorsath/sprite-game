#ifndef DRAWABLES_LEVEL_HPP
#define DRAWABLES_LEVEL_HPP

class Level: public Drawable {
  private:
    struct ChunkData {
      int x;
      int y;
      int n;
    };

  public:
    Level(std::string file);
    void draw(float dt);
    void setup();
    void setTexture(Texture* texture);
    void save();
    void load();

    Chunk* loadChunk(ChunkData chunkData);
    Chunk* findChunk(Vec2 position);

  private:

    std::vector<Chunk*> chunks;

    std::string filename_;
    std::vector<ChunkData> data_;
    Texture* texture_;

    
};

#endif




