#include "config.hpp"

int main(){
  display::setup();
  display::camera = Vec2(-8, -8);

  Builder* builder = new Builder();

  Level* level = new Level("./resources/level_1/level.dat");

  builder->setLevel(level);
  display::add_to_draw(builder);

  display::draw();

  return 0;
}


