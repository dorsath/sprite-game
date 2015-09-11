#ifndef DRAWABLES_PLAYER_HPP
#define DRAWABLES_PLAYER_HPP

class Player: public Drawable {
  public:
    void draw();
    void setup();
    Player(const char* name, int x, int y);

  private:
    const char* name_;
    float position_[2];
    Model model;
    Texture texture_;
    Program program;
    void generateModel();
};

#endif


