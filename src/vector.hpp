#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vec2 {
  public:
    void set(float x_in, float y_in);
    float x;
    float y;

    Vec2 operator*(float val);
    Vec2 operator+(Vec2 b);
    void operator+=(Vec2 b);

    Vec2();
    Vec2(float x_in, float y_in);

    


};

#endif



