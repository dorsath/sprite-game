#include "../config.hpp"

Item::Item(int x, int y, int spriteID, int animationLength){
  position_[0] = x;
  position_[1] = y;

  spriteID_ = spriteID;
  animationLength_ = animationLength;
}

void Item::draw(){

  program.use();
    if (animationLength_ > 1 && (glfwGetTime() - lastTime) > 0.2){
      animate();
      lastTime = glfwGetTime();
    }

    glUniform1i(program.uniform("sprites"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  texture_->getID());

    glBindVertexArray(model.vao);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

    glUniform2f(program.uniform("position"), position_[0], position_[1]);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, model.verticesCount);

    glDisableVertexAttribArray(0);
  glUseProgram(0);

}

void Item::animate(){
  int currentSpriteID = spriteID_ + rand() % animationLength_;
  float xSprite = float(currentSpriteID % 64);
  float ySprite = float(currentSpriteID / 64);
  glUniform2f(program.uniform("sprite"), xSprite, ySprite);
}

void Item::setup(){
  program.build("item");
  program.getUniformLocation("sprites");
  program.getUniformLocation("sprite");
  program.getUniformLocation("position");
  lastTime = glfwGetTime();

  generateModel();
}

void Item::setTexture(Texture* texture){
  texture_ = texture;
}


void Item::generateModel(){
  float vertices[12] = {
    //Vertices
    0, 0,
    1, 1,
    0, 1,

    0, 0,
    1, 0,
    1, 1,
  };

  model.create(vertices, 12);
}