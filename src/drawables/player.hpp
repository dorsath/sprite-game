#ifndef DRAWABLES_PLAYER_HPP
#define DRAWABLES_PLAYER_HPP

class Player: public Drawable {
  public:
    void draw(float dt);
    void setup();
    Player(const char* name, int x, int y);
    void handleKeys();

  private:
    const char* name_;
    float speed_;
    Model model;
    Texture texture_;
    Program program;
    bool mirror_;
    bool moving_;
    float direction_;
    float animation_;

    Vec2 position_;
    Vec2 velocity_;
    float movementSpeed_;
    float timeSinceAnimation;

    void generateModel();
    void animate(int row);

    const int animations_[10] = {4, 4, 4, 4, 4 ,4, 4, 6, 6, 6};
};

#endif


