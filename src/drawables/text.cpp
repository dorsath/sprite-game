#include "../config.hpp"

void Text::draw(float dt){


  program.use();


  glUniform1i(program.uniform("font"), 0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,  font.textureID);


  glBindVertexArray(model.vao);
  glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

  if (textUpdated){
    updateText();
  }

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, model.verticesCount);
  glDisableVertexAttribArray(0);

  glUseProgram(0);
}

void Text::setText(std::string input_text){
  textUpdated = true;
  text = input_text;
}


void Text::updateText(){
  std::vector<int> codes;
  for(char& c : text) {
    codes.push_back(int(c) - 32);
  }
  glUniform1iv(program.uniform("text"), text.size(), &codes[0]);
  textUpdated = false;
}


Text::Text(std::string input_text, float x_0, float y_0){
  text = input_text;
  x = x_0;
  y = y_0;
}

void Text::generateModel(std::string input_text){
  std::vector<float> vertices;
  int i = 0;
  for(char& c : input_text) {
    //std::cout << (int)c << std::endl;

    float x_offset = i;

    float newVertices[12] = {
      x_offset    , 0,
      x_offset + 1, 1,
      x_offset    , 1,

      x_offset    , 0,
      x_offset + 1, 0,
      x_offset + 1, 1
    };

    vertices.insert(vertices.end(), newVertices, newVertices + 12);
    i += 1;
  }

  model.verticesCount = vertices.size();
  model.create(vertices);
}

void Text::setup(){
  program.build("text");
  program.getUniformLocation("text");
  program.getUniformLocation("font");
  generateModel(text);

  
  std::vector<int> codes;
  for(char& c : text) {
    codes.push_back(int(c) - 32);
  }
  glUniform1iv(program.getUniformLocation("text"), text.size(), &codes[0]);
  
  glUniform2f(program.getUniformLocation("position"), x, y);
  font.setup();

}
