#ifndef TEXT_HPP
#define TEXT_HPP


class Text: public Drawable {

  private:
    struct Line {
      Model model;
      std::string text;
    };
    struct Cursor {
      int line;
      int column;
    };

    bool textUpdated;

  public:
    Font font;
    Program program;
    Model model;
    GLuint textureID;
    std::string text;
    float x;
    float y;

    void setText(std::string input_text);
    void updateText();
    void draw(float dt);
    void setup();
    void generateTexture(std::string text);
    void generateModel(std::string text);
    Text(std::string text, float x_0, float y_0);



};

#endif

