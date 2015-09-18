#include "../config.hpp"

Item::Item(int x, int y, int spriteID, int animationLength){
  position_.x = x;
  position_.y = y;

  texture_ = Texture::find_or_create("DungeonCrawl_ProjectUtumnoTileset.png");
  spriteID_ = spriteID;
  animationLength_ = animationLength;
  animationTimeout_.setTimeLimit(0.15);
}

void Item::draw(float dt){

  program.use();
    animationTimeout_.tick(dt);
    if (animationLength_ > 1 && animationTimeout_.ready()){
      animate();
      animationTimeout_.reset();
    }

    glUniform1i(program.uniform("sprites"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  texture_->getID());

    glBindVertexArray(model.vao);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

    glUniform2f(program.uniform("position"), position_.x + display::camera.x, position_.y + display::camera.y);

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
  //lastTime = glfwGetTime();

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
