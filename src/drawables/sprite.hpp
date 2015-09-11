#ifndef SPRITE_HPP
#define SPRITE_HPP

class Sprite: public Drawable {

  public:
    Model model;
    Program program;
    //Font font;
    GLuint textureID;
    //std::string text;
    //float x;
    //float y;

    void draw(float dt);
    void setup();
    void generateModel();
    void generateTexture();
    void click_callback(int button, int action, int modifiers, Coordinate mouseCoord);
    //Text(std::string text, float x_0, float y_0);



};

#endif


