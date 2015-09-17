#include "config.hpp"

int main(){
  display::setup();

  Texture* spritesTexture = new Texture();
  spritesTexture->load("./textures/DungeonCrawl_ProjectUtumnoTileset.png");

  Builder* builder = new Builder();
  Chunk* chunk = new Chunk("./resources/level_1/1.dat", Vec2(-0.5, -0.5));
  chunk->setTexture(spritesTexture);

  builder->setChunk(chunk);

  display::add_to_draw(builder);

  display::draw();

  return 0;
}


