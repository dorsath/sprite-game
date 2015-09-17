#include "config.hpp"

int main(void) {

  display::setup();


  Texture* spritesTexture = new Texture();
  spritesTexture->load("./textures/DungeonCrawl_ProjectUtumnoTileset.png");

  Chunk* chunk = new Chunk("./resources/level_1/test.raw");
  chunk->setTexture(spritesTexture);

  Item* brazier = new Item(-1, 0, 781, 8);
  brazier->setTexture(spritesTexture);
  FPSMeter* fpsCounter = new FPSMeter();

  Player* player = new Player("Ronald", 0, 0);

  display::add_to_draw(chunk);
  display::add_to_draw(fpsCounter);
  display::add_to_draw(brazier);
  display::add_to_draw(player);
  

  display::draw();

}

