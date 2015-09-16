#include "../config.hpp"

Player::Player(const char* name, int x, int y){
  name_ = name;
  position_.set(x,y);
  speed_ = 1.0;
  direction_ = 2;
  animation_ = 0.0;
  mirror_ = false;
  movementSpeed_ = 2.0;
  fireRate = 2.0; //attacks per second (Hz)
  shootingSpeed = 3.0;


}

void Player::setup(){
  //Player setup
  program.build("player");
  program.use();

  program.getUniformLocation("direction");
  program.getUniformLocation("animation");
  program.getUniformLocation("mirror");
  program.getUniformLocation("position");
  program.getUniformLocation("sprite");

  generateModel(&model);
  texture_.load("./textures/wizard.png");

  glUseProgram(0);
}

void Player::generateModel(Model* model){
  float newVertices[12] = {
    //Vertices
    0, 0,
    1, 1,
    0, 1,

    0, 0,
    1, 0,
    1, 1,
  };

  model->create(newVertices, 12);
}


void Player::draw(float dt){
  timeSinceShot += dt;
  handleKeys();

  program.use();
    timeSinceAnimation += dt;
    //position_ = position_ + velocity_ * dt;
    display::camera += velocity_ * -dt;
    glUniform2f(program.uniform("position"), position_.x, position_.y);

    float dir = directionsMap[direction_];
    if (!moving_){
      dir += 3;
    }

    if (timeSinceAnimation > 0.2){
      animate((int) dir);
      timeSinceAnimation = 0.0;
    }

    glUniform1i(program.uniform("sprite"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  texture_.getID());

    glUniform1i(program.uniform("direction"), dir);

    glUniform1i(program.uniform("animation"), animation_);
    glUniform1i(program.uniform("mirror"), mirror_);

    glBindVertexArray(model.vao);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, model.verticesCount);
    glDisableVertexAttribArray(0);
}

void Player::animate(int row){
  animation_ = (float) (int(animation_ + 1) % animations_[row]);
}

void Player::handleKeys(){
  velocity_.set(0, 0);

  moving_ = false;
  if (display::keys[87]){ //W
    moving_ = true;
    mirror_ = false;
    animation_ = 0.0;
    direction_ = 0;
    velocity_.set(0, movementSpeed_);
  }

  if (display::keys[65]){ //A
    moving_ = true;
    mirror_ = true;
    direction_ = 3;
    animation_ = 0.0;
    velocity_.set(-movementSpeed_, 0);
  }

  if (display::keys[83]){ //S
    moving_ = true;
    mirror_ = false;
    direction_ = 2;
    animation_ = 0.0;
    velocity_.set(0, -movementSpeed_);
  }

  if (display::keys[68]){ //D
    moving_ = true;
    mirror_ = false;
    direction_ = 1;
    animation_ = 0.0;
    velocity_.set(movementSpeed_, 0);
  }
}


