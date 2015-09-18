#include "../config.hpp"

Builder::Builder(){
  tool_ = 835;
  display::Register reg = {this, 0, 0, 1, 1};
  display::clickRegisters.push_back(reg);
  mode_ = BUILD_MODE;
  saveTimeout.setTimeLimit(0.3);
  moveTimeout.setTimeLimit(0.3);
  position_ = Vec2(0, 0);
}


void Builder::click_callback(int button, int action, int modifiers, Coordinate mouseCoord){
  std::cout << "button: " << button << "action: " << action << std::endl;
  if (button == 0) {
    if (mode_ == BUILD_MODE){
      if (action == 0){
        Coordinate tileLocation = {
          mouseCoord.x * chunk_->width  / display::windowSize.x,
          chunk_->height - mouseCoord.y * chunk_->height / display::windowSize.y};

        tileLocation.y -= 1;

        int xVector = tileLocation.x - tileLocationFrom.x;
        if (xVector != 0) {
          xVector = xVector / abs(xVector);
        } else {
          xVector = 1;
        }

        int yVector = tileLocation.y - tileLocationFrom.y;
        if (yVector != 0) {
          yVector = yVector / abs(yVector);
        } else {
          yVector = 1;
        }

        for (int y = tileLocationFrom.y; y != tileLocation.y + yVector; y += yVector){
          for (int x = tileLocationFrom.x; x != tileLocation.x + xVector; x += xVector){
            Coordinate n = {x,y};
            chunk_->setTile(n, tool_);
          }
        }
      }
      if (action == 1) {
        tileLocationFrom.x = mouseCoord.x * chunk_->width  / display::windowSize.x;
        tileLocationFrom.y = chunk_->height - mouseCoord.y * chunk_->height / display::windowSize.y - 1;
      }
    }

    if (mode_ == SELECT_MODE && action == 0){
      Coordinate tileLocation = {
        mouseCoord.x * 64 / display::windowSize.x,
        mouseCoord.y * 48 / display::windowSize.y};
      tool_ = tileLocation.x + tileLocation.y * 64;
      std::cout << "Current tool: " << tool_ << "\n";
      mode_ = BUILD_MODE;
    }
  }

  if (button == 1 && action == 0){
    if (mode_ == BUILD_MODE){
      mode_ = SELECT_MODE;
    }
  }
}

void Builder::draw(float dt){
  if (mode_ == BUILD_MODE){
    buildKeyHandles(dt);
    chunk_->draw(dt);
  } else { 
    sprite_->draw(dt);
  }
}

void Builder::buildKeyHandles(float  dt){
  saveTimeout.tick(dt);
  moveTimeout.tick(dt);
  if (display::keys[32] && saveTimeout.ready()){
    std::cout << "saving" << std::endl;
    level_->save();
    std::cout << "saved" << std::endl;

    saveTimeout.reset();

  }
  if (moveTimeout.ready()){
    if (display::keys[263]){ //left
      position_ += Vec2(-1, 0);
      std::cout << position_.x << ":" << position_.y << std::endl;
      moveToChunk(position_);
      moveTimeout.reset();
    }

    if (display::keys[262]){ //right
      position_ += Vec2(1, 0);
      std::cout << position_.x << ":" << position_.y << std::endl;
      moveToChunk(position_);
      moveTimeout.reset();
    }

    if (display::keys[265]){ //up
      position_ += Vec2(0, 1);
      std::cout << position_.x << ":" << position_.y << std::endl;
      moveToChunk(position_);
      moveTimeout.reset();
    }

    if (display::keys[264]){ //down
      position_ += Vec2(0, -1);
      std::cout << position_.x << ":" << position_.y << std::endl;
      moveToChunk(position_);
      moveTimeout.reset();
    }
  }

}

void Builder::moveToChunk(Vec2 position){
  display::camera = position_ * -16 + Vec2(-8, -8);
  chunk_ = level_->findChunk(position);
}

void Builder::setLevel(Level* level){
  level_ = level;
}

void Builder::setup(){
  sprite_ = new Sprite;
  level_->setup();
  moveToChunk(position_);
  //chunk_->setup();
  sprite_->setup();
}
