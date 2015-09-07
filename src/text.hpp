#ifndef TEXT_HPP
#define TEXT_HPP

class Text: public Drawable {

  public:
    Model model;
    Font font;
    Program program;
    GLuint textureID;
    std::string text;
    float x;
    float y;

    void draw();
    void setup();
    void generateTexture(std::string text);
    Text(std::string text, float x_0, float y_0);



};

#endif

