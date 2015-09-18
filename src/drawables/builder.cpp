#include "../config.hpp"

Builder::Builder(){
  tool_ = 835;
  display::Register reg = {this, 0, 0, 1, 1};
  display::clickRegisters.push_back(reg);
  mode_ = BUILD_MODE;
  timeSinceSaveAction = 0.0;
  timeSinceMoveAction = 0.0;
  saveActionTimeout = 0.3;
  moveActionTimeout = 0.3;
  position_ = Vec2(0, 0);
}


void Builder::click_callback(int button, int action, int modifiers, Coordinate mouseCoord){
  std::cout << "button: " << button << std::endl;
  if (button == 0 && action == 0) {
    if (mode_ == BUILD_MODE){
      Coordinate tileLocation = {
        mouseCoord.x * chunk_->width  / display::windowSize.x,
        chunk_->height - mouseCoord.y * chunk_->height / display::windowSize.y};

      tileLocation.y -= 1;
      chunk_->setTile(tileLocation, tool_);
    }

    if (mode_ == SELECT_MODE){
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
  timeSinceSaveAction += dt;
  timeSinceMoveAction += dt;
  if (display::keys[32] && timeSinceSaveAction > saveActionTimeout){
    std::cout << "saving" << std::endl;
    level_->save();
    std::cout << "saved" << std::endl;

    timeSinceSaveAction = 0.0;

  }
  if (timeSinceMoveAction > moveActionTimeout){
    if (display::keys[263]){ //left
      position_ += Vec2(-1, 0);
      std::cout << position_.x << ":" << position_.y << std::endl;
      moveToChunk(position_);
      timeSinceMoveAction = 0.0;
    }

    if (display::keys[262]){ //right
      position_ += Vec2(1, 0);
      std::cout << position_.x << ":" << position_.y << std::endl;
      moveToChunk(position_);
      timeSinceMoveAction = 0.0;
    }

    if (display::keys[265]){ //up
      position_ += Vec2(0, 1);
      std::cout << position_.x << ":" << position_.y << std::endl;
      moveToChunk(position_);
      timeSinceMoveAction = 0.0;
    }

    if (display::keys[264]){ //down
      position_ += Vec2(0, -1);
      std::cout << position_.x << ":" << position_.y << std::endl;
      moveToChunk(position_);
      timeSinceMoveAction = 0.0;
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
