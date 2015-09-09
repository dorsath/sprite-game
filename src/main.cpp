#include "config.hpp"

int main(void) {

  display::setup();

  std::vector<int> chunkData(32 * 32, 960);
  chunkData[1] = 832;
  Chunk* chunk = new Chunk(chunkData);

  Text* fpsCounter = new Text("spf:       ", -1, -1);
  display::add_to_draw(chunk);
  display::add_to_draw(fpsCounter);
  

  display::draw();

}

