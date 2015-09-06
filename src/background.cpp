#include "config.hpp"

void Background::draw(){
  //draw object
  
  glUseProgram(program);

  glCullFace(GL_FRONT);
  glBindVertexArray(cube.vao);
  glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(cube.verticesCount * 4 * sizeof(float)));

  glUniformMatrix4fv(modelViewMatrixUnif, 1, GL_FALSE, (display::perspectiveMatrix * modelMatrix ).get());
  
  glDrawArrays(GL_TRIANGLES, 0, cube.verticesCount);


  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  glUseProgram(0);
}

void Background::setup(){
  cube.load("./models/cube.raw");

  display::BuildProgram("background", &program);

  modelMatrix.identity();
  modelMatrix.scale(40, 10, 10);
  modelMatrix.translate(0,0.5, 2.2);

  modelViewMatrixUnif = glGetUniformLocation(program, "modelViewMatrix");

}


