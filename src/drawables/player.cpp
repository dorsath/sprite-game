#include "../config.hpp"

Player::Player(const char* name, int x, int y){
  name_ = name;
  position_[0] = float(x);
  position_[1] = float(y);
}

void Player::setup(){
  program.build("player");
  program.use();

  program.getUniformLocation("direction");
  program.getUniformLocation("animation");
  program.getUniformLocation("position");
  program.getUniformLocation("sprite");

  glUniform1i(program.uniform("direction"), 8);
  glUniform1i(program.uniform("animation"), 0);

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

void Player::draw(){
  program.use();
    glUniform1i(program.uniform("sprite"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  texture_.getID());

    glBindVertexArray(model.vao);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

    glUniform2f(program.uniform("position"), position_[0], position_[1]);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, model.verticesCount);
    glDisableVertexAttribArray(0);
  glUseProgram(0);

}


