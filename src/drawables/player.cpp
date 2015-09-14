#include "../config.hpp"

Player::Player(const char* name, int x, int y){
  name_ = name;
  position_.set(x,y);
  speed_ = 1.0;
  direction_ = 5.0;
  animation_ = 0.0;
  mirror_ = false;
  int animations[10] = {4, 4, 4, 4, 4 ,4, 4, 6, 6, 6};
  movementSpeed_ = 2.0;
  animations_.insert(animations_.begin(), animations, animations + 10);
}

void Player::setup(){
  program.build("player");
  program.use();

  program.getUniformLocation("direction");
  program.getUniformLocation("animation");
  program.getUniformLocation("mirror");
  program.getUniformLocation("position");
  program.getUniformLocation("sprite");


  glUseProgram(0);

  generateModel();
  std::cout << model.verticesCount << std::endl;
  texture_.load("./textures/wizard.png");
}

void Player::generateModel(){
  float newVertices[12] = {
    //Vertices
    0, 0,
    1, 1,
    0, 1,

    0, 0,
    1, 0,
    1, 1,
  };

  model.create(newVertices, 12);
}


void Player::draw(float dt){
  handleKeys();

  program.use();
    timeSinceAnimation += dt;
    position_ = position_ + velocity_ * dt;
    glUniform2f(program.uniform("position"), position_.x, position_.y);

    if (timeSinceAnimation > 0.2){
      animate();
      timeSinceAnimation = 0.0;
    }

    glUniform1i(program.uniform("sprite"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  texture_.getID());

    if (moving_){
      glUniform1i(program.uniform("direction"), direction_);
    } else {
      glUniform1i(program.uniform("direction"), direction_ + 3);
    }

    glUniform1i(program.uniform("animation"), animation_);
    glUniform1i(program.uniform("mirror"), mirror_);

    glBindVertexArray(model.vao);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, model.verticesCount);
    glDisableVertexAttribArray(0);
  glUseProgram(0);

}

void Player::animate(){
  animation_ = (float) (int(animation_ + 1) % animations_[int(direction_)]);
}

void Player::handleKeys(){
  velocity_.set(0, 0);

  moving_ = false;
  if (display::keys[87]){
    moving_ = true;
    mirror_ = false;
    direction_ = 5.0;
    velocity_.set(0, movementSpeed_);
  }

  if (display::keys[65]){
    moving_ = true;
    mirror_ = true;
    direction_ = 4.0;
    velocity_.set(-movementSpeed_, 0);
  }

  if (display::keys[68]){
    moving_ = true;
    mirror_ = false;
    direction_ = 4.0;
    velocity_.set(movementSpeed_, 0);
  }

  if (display::keys[83]){
    moving_ = true;
    mirror_ = false;
    direction_ = 6.0;
    velocity_.set(0, -movementSpeed_);
  }
}


