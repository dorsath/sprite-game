#ifndef DRAWABLES_ITEM_HPP
#define DRAWABLES_ITEM_HPP

class Item: public Drawable {
  public:
    void draw(float dt);
    void setup();
    Item(int x, int y, int spriteID, int animationLength);
    void setTexture(Texture* texture);

  private:
    Model model;
    Texture* texture_;
    Program program;

    int spriteID_;
    int animationLength_;


    float timeSinceAnimation;
    Vec2 position_;
    
    void generateTexture();
    void generateModel();
    void animate();
};

#endif

