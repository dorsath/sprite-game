#include "config.hpp"

void Program::build(const char* name){
  char shaderName[50];
  std::vector<GLuint> shaderList;

  sprintf(shaderName, "%s.vert", name);
  shaderList.push_back(display::CreateShader(GL_VERTEX_SHADER, shaderName));

  sprintf(shaderName, "%s.frag", name);
  shaderList.push_back(display::CreateShader(GL_FRAGMENT_SHADER, shaderName));

  programID = display::CreateProgram(shaderList);
  std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

void Program::use(){
  glUseProgram(programID);
}

GLuint Program::getUniformLocation(const char* name){
  use();
  GLuint unif = glGetUniformLocation(programID, name); 
  uniformLocations[name] = unif;
  return unif;
}

GLuint Program::uniform(const char* name){
  return uniformLocations[name];
}
