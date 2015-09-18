#include "config.hpp"

int main(){
  display::setup();

  Texture* spritesTexture = new Texture();
  spritesTexture->load("./textures/DungeonCrawl_ProjectUtumnoTileset.png");

  Builder* builder = new Builder();

  Level* level = new Level("./resources/level_1/level.dat");
  level->setTexture(spritesTexture);

  //Chunk* chunk = new Chunk("./resources/level_1/1.dat", Vec2(-0.5, -0.5));
  //chunk->setTexture(spritesTexture);

  builder->setLevel(level);
  display::add_to_draw(builder);
  display::camera = Vec2(-8, -8);

  display::draw();

  return 0;
}


