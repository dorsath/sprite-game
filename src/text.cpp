#include "config.hpp"

void Text::draw(){

  program.use();


  glUniform1i(program.uniform("font"), 0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,  font.textureID);


  int lineNr = 0;
  for(Line* line: lines) {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glUniform1i(program.uniform("lineNr"), lineNr);
    drawLine(line->model);
    lineNr += 1;

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
  }

  glUseProgram(0);

}

void Text::drawLine(Model model){

  glBindVertexArray(model.vao);
  glBindBuffer(GL_ARRAY_BUFFER, model.vbo);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  GLvoid const* pointer = static_cast<char const*>(0) + model.verticesCount * 4;
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, pointer);

  glDrawArrays(GL_TRIANGLES, 0, model.verticesCount);

}


Text::Text(std::string input_text, float x_0, float y_0){
  text = input_text;
  x = x_0;
  y = y_0;
}

void Text::generateModel(Model* model, std::string input_text){
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
    model->create(vertices);
  }

  model->verticesCount = vertices.size();

  for(char& c : input_text) {
    int code = (int) c;
    code -= 32;

    float character[2] = { float(code % 16), float(code/16) };
    for (int i = 0; i < 6; ++i)
      vertices.insert(vertices.end(), character, character + 2);
  }

  model->create(vertices);
}

void Text::key_callback(int key, int mods){
  std::cout << key << ":" << mods << std::endl;

  int code = key - 32;
  if (key == 259){
    cursor.column--;
    writeLetter(0);
  }
  if (key == 257){
    newLine();
    cursor.column = 0;
    cursor.line += 1;
  }

  if (key < 256){
    if (key >= 65 && key <= 90)
      code += 32;

    if (mods)
      code -= 32;
    writeLetter(code);
    cursor.column++;
  }

}

void Text::newLine(){
  Line* newLine = new Line;
  generateModel(&newLine->model, "                                                                                ");
  lines.push_back(newLine);
  
  std::cout << lines[0]->model.verticesCount << "\n";
}

void Text::writeLetter(int code){
  std::vector<float> vertices;
  float character[2] = { float(code % 16), float(code/16) };
  for (int i = 0; i < 6; ++i)
    vertices.insert(vertices.end(), character, character + 2);

  glBindBuffer(GL_ARRAY_BUFFER, lines[cursor.line]->model.vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 3840 + cursor.column * 48, 48, &vertices[0]);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Text::setup(){
  program.build("text");
  program.getUniformLocation("text");
  program.getUniformLocation("font");
  program.getUniformLocation("lineNr");
  newLine();
  cursor.line = 0;
  cursor.column = 0;
  
  glUniform2f(program.getUniformLocation("position"), x, y);
  font.setup();


}
