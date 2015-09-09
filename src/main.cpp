#include "config.hpp"

int main(void) {

  display::setup();


  Texture* spritesTexture = new Texture("./textures/DungeonCrawl_ProjectUtumnoTileset.png");

  std::vector<int> chunkData(32 * 32, 960);
  chunkData[1] = 832;
  Chunk* chunk = new Chunk(chunkData);
  chunk->setTexture(spritesTexture);

  Item* brazier = new Item(0, 0, 781, 8);
  brazier->setTexture(spritesTexture);
  Text* fpsCounter = new Text("spf:       ", -1, -1);

  display::add_to_draw(chunk);
  display::add_to_draw(fpsCounter);
  display::add_to_draw(brazier);
  

  display::draw();

}

