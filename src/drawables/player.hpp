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
    float position_[2];
    float speed_;
    Model model;
    Texture texture_;
    Program program;
    bool mirror_;
    bool moving_;
    float direction_;
    float animation_;
    float velocity_[2];
    float movementSpeed_;
    std::vector<int> animations_;
    float timeSinceAnimation;

    void generateModel();
    void animate();
};

#endif


