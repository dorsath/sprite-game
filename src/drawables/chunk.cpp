#include "../config.hpp"

Chunk::Chunk(std::vector<int> data){
  width = 32;
  height = 32;
  data_.insert(data_.begin(), data.begin(), data.end());
}

Chunk::Chunk(){
  width = 16;
  height = 16;
  std::vector<int> chunkData(width * height, 960);
  data_.insert(data_.begin(), chunkData.begin(), chunkData.end());
}

void Chunk::draw(float dt){
  program.use();
    glUniform1i(program.uniform("sprites"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  texture_->getID());

    glBindVertexArray(model.vao);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

    glUniform2f(program.uniform("position"), position[0], position[1]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    GLvoid const* pointer = static_cast<char const*>(0) + model.verticesCount * 4;
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, pointer);

    glDrawArrays(GL_TRIANGLES, 0, model.verticesCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
  glUseProgram(0);
}

void Chunk::setup(){
  generateModel();
  program.build("chunk");
  program.getUniformLocation("sprites");
  program.getUniformLocation("position");
  position[0] = -8;
  position[1] = -8;
}

void Chunk::setTexture(Texture* texture){
  texture_ = texture;
}

void Chunk::setTile(Coordinate tileLocation, int spriteNr){
  float spriteWidth  = 1.0f / 64.0f;
  float spriteHeight = 1.0f / 48.0f;

  float xSprite = float(spriteNr % 64) * spriteWidth;
  float ySprite = (47 - float(spriteNr / 64)) * spriteHeight;
  
  float newVertices[12] = {
    xSprite               , ySprite    ,
    xSprite + spriteWidth , ySprite + spriteHeight,
    xSprite               , ySprite + spriteHeight,

    xSprite               , ySprite    ,
    xSprite + spriteWidth , ySprite    ,
    xSprite + spriteWidth , ySprite + spriteHeight
  };

  std::cout << newVertices[0] << ":" << newVertices[1] << "\n";
  std::cout << newVertices[2] << ":" << newVertices[3] << "\n";

  int verticesOffset = width * height * 12 * sizeof(float);
  int textureCoordOffset = (tileLocation.x + tileLocation.y * width) * 12 * sizeof(float);

  glBindBuffer(GL_ARRAY_BUFFER, model.vbo);
  glBufferSubData(GL_ARRAY_BUFFER, verticesOffset + textureCoordOffset, 12 * sizeof(float), newVertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Chunk::generateModel(){
  float xOffset;
  float yOffset;

  float xSprite;
  float ySprite;
  int spriteNr;

  float spriteWidth  = 1.0f / 64.0f;
  float spriteHeight = 1.0f / 48.0f;

  printf("sprite size: %.2f:%.2f\n", spriteWidth, spriteHeight);
  std::vector<float> vertices;

  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      spriteNr = data_[x + y * width];
      xSprite = float(spriteNr % 64) * spriteWidth;
      ySprite = (47 - float(spriteNr / 64)) * spriteHeight;

      xOffset = (int)x;
      yOffset = (int)y;

      
      float newVertices[24] = {
        //Vertices
        xOffset    , yOffset    ,
        xOffset + 1, yOffset + 1,
        xOffset    , yOffset + 1,

        xOffset    , yOffset    ,
        xOffset + 1, yOffset    ,
        xOffset + 1, yOffset + 1,
        //Texcoords
        xSprite               , ySprite    ,
        xSprite + spriteWidth , ySprite + spriteHeight,
        xSprite               , ySprite + spriteHeight,

        xSprite               , ySprite    ,
        xSprite + spriteWidth , ySprite    ,
        xSprite + spriteWidth , ySprite + spriteHeight
      };


      vertices.insert(vertices.begin() + vertices.size() / 2, newVertices, newVertices + 12);
      vertices.insert(vertices.end(), newVertices + 12, newVertices + 24);
    }
  }
  model.verticesCount = vertices.size() / 2;
  printf("vertices size: %lu\n", vertices.size() * sizeof(float));
  model.create(vertices);
}

