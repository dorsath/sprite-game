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
    Model model;
    Texture* texture_;
    Program program;
    bool mirror_;
    bool moving_;
    int direction_;
    float animation_;

    Vec2 position_;
    Vec2 velocity_;
    float movementSpeed_;
    Timeout animationTimeout_;

    void generateModel(Model* model);
    void animate(int row);

    static const int animations_[];
    static const float directionsMap[];

};

#endif
