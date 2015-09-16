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
    Sprite* sprite_;
    int tool_;

    int mode_;

    void buildKeyHandles(float dt);


    float timeSinceSaveAction;
    float saveActionTimeout;
    static const int BUILD_MODE = 0;
    static const int SELECT_MODE = 1;
};
#endif



