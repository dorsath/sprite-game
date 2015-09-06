#include "config.hpp"

void Text::draw(){

  program.use();

    glUniform1i(program.uniform("font"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  font.textureID);

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

//void Text::generateTexture(std::string text){
//  std::vector<int> textInts;
//  for(char& c : text) {
//    textInts.push_back( (int)c);
//  }
//  
//  glGenTextures(1, &textureID);
//  glBindTexture(GL_TEXTURE_1D, textureID);
//  glTexImage1D(GL_TEXTURE_1D, 0, GL_RED, text.size(), 0, GL_RED, GL_INT, &textInts[0]);
//  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//  glBindTexture(GL_TEXTURE_1D, 0);
//}

void Text::setup(){

  std::string text("Hello world!");

  program.build("text");
  program.getUniformLocation("text");
  program.getUniformLocation("font");
  font.setup();

  model.create(text);

}
