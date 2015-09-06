
class Polygon: public Drawable {

  public:
    Model model;
    Program theProgram;
    void draw();
    void setup();
    void keys();
    Matrix4 modelMatrix;

};

