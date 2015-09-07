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

Text::Text(std::string input_text, float x_0, float y_0){
  text = input_text;
  x = x_0;
  y = y_0;
}

void Text::setup(){
  program.build("text");
  program.getUniformLocation("text");
  program.getUniformLocation("font");
  
  glUniform2f(program.getUniformLocation("position"), x, y);
  font.setup();

  model.create(text);

}
