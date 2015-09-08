#include "config.hpp"


void Sprite::draw(){
  program.use();
    glUniform1i(program.uniform("sprites"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  textureID);

    glBindVertexArray(model.vao);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, model.verticesCount);

    glDisableVertexAttribArray(0);
  glUseProgram(0);
}

void Sprite::generateTexture(){
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

void Sprite::generateModel(){
  float newVertices[12] = {
    -1, -1,
     1,  1,
    -1,  1,

    -1, -1,
     1, -1,
     1,  1
  };

  model.verticesCount = 6;
  std::vector<float> vertices;
  vertices.insert(vertices.begin(), newVertices, newVertices + 12);
  model.create(vertices);
}

void Sprite::click_callback(int button, int action, int modifiers, Coordinate mouseCoord) {
  Coordinate clickCoord;
  clickCoord.x = float(mouseCoord.x) / float(display::windowSize.x) * 64;
  clickCoord.y = float(mouseCoord.y) / float(display::windowSize.y) * 48;
  std::cout << clickCoord.x << ":" << clickCoord.y << "\n";
}

void Sprite::setup(){
  program.build("sprite_selector");
  program.getUniformLocation("sprites");

  generateModel();
  generateTexture();
}
