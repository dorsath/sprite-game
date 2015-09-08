#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

class Drawable {

  public:
    virtual void draw(){ printf("No draw defined"); }
    virtual void setup(){ printf("No setup defined"); }
    virtual void scroll_callback(double yoffset){ printf("no scroll callback defined\n"); }
    virtual void key_callback(int key, int mods) {}
};
#endif
