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

  public:
    Font font;
    Program program;
    GLuint textureID;
    std::string text;
    std::vector<Line*> lines;
    Cursor cursor;
    float x;
    float y;

    void draw();
    void setup();
    void drawLine(Model model);
    void newLine();
    void key_callback(int key, int mods);
    void writeLetter(int key);
    void generateTexture(std::string text);
    void generateModel(Model* model, std::string text);
    Text(std::string text, float x_0, float y_0);



};

#endif

