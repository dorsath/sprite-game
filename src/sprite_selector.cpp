#include "config.hpp"

int main(void) {

  display::setup();

  Sprite* sprite = new Sprite;
  display::add_to_draw(sprite);
  display::Register spriteRegister = {sprite, 0, 0, 1, 1};
  display::clickRegisters.push_back(spriteRegister);

  display::draw();

}


