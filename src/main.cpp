#include "config.hpp"

int main(void) {

  display::setup();

  Chunk* chunk = new Chunk;
  display::add_to_draw(chunk);

  display::draw();

}

