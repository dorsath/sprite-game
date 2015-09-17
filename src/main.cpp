#include "config.hpp"

int main(void) {

  display::setup();

  Texture* spritesTexture = new Texture();
  spritesTexture->load("./textures/DungeonCrawl_ProjectUtumnoTileset.png");

  Level* level = new Level("./resources/level_1/level.dat");
  level->setTexture(spritesTexture);

  Item* brazier = new Item(-1, 0, 781, 8);
  brazier->setTexture(spritesTexture);
  FPSMeter* fpsCounter = new FPSMeter();

  Player* player = new Player("Ronald", 8, 8);

  display::add_to_draw(level);
  display::add_to_draw(fpsCounter);
  display::add_to_draw(brazier);
  display::add_to_draw(player);
  

  display::draw();

}

