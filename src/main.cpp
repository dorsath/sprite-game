#include "config.hpp"

int main(void) {

  display::setup();


  Level* level = new Level("./resources/level_1/level.dat");

  Item* brazier = new Item(8, 5, 781, 8);
  FPSMeter* fpsCounter = new FPSMeter();

  Player* player = new Player("Ronald", 8, 8);

  display::add_to_draw(level);
  display::add_to_draw(fpsCounter);
  display::add_to_draw(brazier);
  display::add_to_draw(player);
  

  display::draw();

}

