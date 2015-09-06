#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

class Background: public Drawable {
  public:
    Model cube;
    GLuint program;
    Matrix4 modelMatrix;
    GLuint modelViewMatrixUnif;

  public:
    void draw();
    void setup();
};

#endif

