#ifndef SLICE_HPP
#define SLICE_HPP

class Slice: public Drawable {
  public:
    float depth;
    int mode;
    Model square;
    Program sliceProgram;
    Octree octree;

    GLuint octree_unif;
    GLuint depth_unif;
    GLuint mode_unif;

    void draw();
    void setup();
    void scroll_callback(double yoffset);

};
#endif

