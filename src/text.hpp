#ifndef TEXT_HPP
#define TEXT_HPP

class Text: public Drawable {

  public:
    Model model;
    Font font;
    Program program;
    GLuint textureID;

    void draw();
    void setup();
    void generateTexture(std::string text);


};

#endif

