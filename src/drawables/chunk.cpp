#include "../config.hpp"


void Chunk::draw(){
  //return;
  program.use();
    glUniform1i(program.uniform("sprites"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  textureID);

    glBindVertexArray(model.vao);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

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
  generateTexture();
  generateModel();
  program.build("chunk");
  program.getUniformLocation("sprites");
}

void Chunk::generateTexture(){
  const char* filepath = "./textures/DungeonCrawl_ProjectUtumnoTileset.png";
  printf("Loading texture ...");
  std::vector<unsigned char> buffer, image;
  lodepng::load_file(buffer, filepath); //load the image file with given filename
  unsigned w, h;
  unsigned error = lodepng::decode(image, w, h, buffer); //decode the png
  printf("(%d, %d)..", w, h);

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
  printf("done\n");
}

void Chunk::generateModel(){
  float xOffset;
  float yOffset;

  float xSprite;
  float ySprite;
  int spriteNr = 960;

  float spriteWidth  = 1.0f / 64.0f;
  float spriteHeight = 1.0f / 48.0f;
  xSprite = float(spriteNr % 64) * spriteWidth;
  ySprite = float(spriteNr / 64) * spriteHeight;

  printf("sprite size: %.2f:%.2f\n", spriteWidth, spriteHeight);
  printf("sprite location: %.2f:%.2f\n", xSprite, ySprite);
  std::vector<float> vertices;

  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
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

Chunk::Chunk(){
  width = 32;
  height = 32;
}

