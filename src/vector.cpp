#include "config.hpp"

void Vec2::set(float x_in, float y_in){
  x = x_in;
  y = y_in;
}

Vec2::Vec2(){
  set(0.0, 0.0);
}

Vec2 Vec2::operator+(Vec2 b){
  return Vec2(x + b.x, y + b.y);
}

void Vec2::operator+=(Vec2 b){
  x += b.x;
  y += b.y;
}

Vec2 Vec2::operator*(float val){
  return Vec2(x *= val, y *= val);
}

Vec2::Vec2(float x_in, float y_in){
  set(x_in, y_in);
}

