#include "config.hpp"

int main(void) {

  display::setup();

  //Text* text = new Text("", -1.0, 0.9);
  //display::add_to_draw(text);

  Sprite* sprite = new Sprite;
  display::add_to_draw(sprite);
  display::Register spriteRegister = {sprite, 0, 0, 1, 1};
  display::clickRegisters.push_back(spriteRegister);

  display::draw();

}

