#include "../config.hpp"

Builder::Builder(){
  tool_ = 835;
  display::Register reg = {this, 0, 0, 1, 1};
  display::clickRegisters.push_back(reg);
}


void Builder::click_callback(int button, int action, int modifiers, Coordinate mouseCoord){
  Coordinate tileLocation = {
    mouseCoord.x * chunk_->width  / display::windowSize.x,
    chunk_->height - mouseCoord.y * chunk_->height / display::windowSize.y};

  tileLocation.y -= 1;
  std::cout << tileLocation.x << ":" << tileLocation.y << "\n";
  chunk_->setTile(tileLocation, tool_);
}

void Builder::draw(float dt){
  chunk_->draw(dt);
}

void Builder::setChunk(Chunk* chunk){
  chunk_ = chunk;
}


void Builder::setup(){
  chunk_->setup();
}
