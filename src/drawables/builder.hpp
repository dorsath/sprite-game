#ifndef DRAWABLES_BUILDER_HPP
#define DRAWABLES_BUILDER_HPP
class Builder: public Drawable {
  public:
    void draw(float dt);
    void setup();
    void setLevel(Level* level);
    void click_callback(int button, int action, int modifiers, Coordinate mouseCoord);
    Builder();

  private:
    Chunk* chunk_;
    Level* level_;
    Sprite* sprite_;
    int tool_;

    int mode_;

    void buildKeyHandles(float dt);
    void moveToChunk(Vec2 position);

    Coordinate tileLocationFrom;
    Vec2 position_;

    float timeSinceSaveAction;
    float timeSinceMoveAction;
    float moveActionTimeout;
    float saveActionTimeout;
    static const int BUILD_MODE = 0;
    static const int SELECT_MODE = 1;
};
#endif
