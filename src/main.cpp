#include "config.hpp"

int main(void) {

  display::setup();

  Text* text = new Text("", -1.0, 0.9);
  display::add_to_draw(text);

  display::draw();

}

