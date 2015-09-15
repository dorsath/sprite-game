#ifndef DRAWABLES_BUILDER_HPP
#define DRAWABLES_BUILDER_HPP
class Builder: public Drawable {
  public:
    void draw(float dt);
    void setup();
    void setChunk(Chunk* chunk);
    void click_callback(int button, int action, int modifiers, Coordinate mouseCoord);
    Builder();

  private:
    Chunk* chunk_;
    int tool_;
};
#endif



