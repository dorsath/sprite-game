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

    void draw();
    void setup();
    void generateModel();
    void generateTexture();
    //Text(std::string text, float x_0, float y_0);



};

#endif


