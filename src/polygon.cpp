#include "config.hpp"

void Polygon::draw(){
  keys();
  theProgram.use();
    glBindVertexArray(model.vao);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);
    glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);

    //glCullFace(GL_FRONT);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, model.colorOffset);
    glUniformMatrix4fv(theProgram.uniform("modelViewMatrix"), 1, GL_FALSE, (display::perspectiveMatrix * modelMatrix ).get());
    glDrawArrays(GL_TRIANGLES, 0, model.verticesCount);

    glDisableVertexAttribArray(0);
  glUseProgram(0);

}

void Polygon::keys(){
  if (display::keys[83]){
    Matrix4 rotation;
    rotation.rotateX(6);
    modelMatrix.translate(-0.5, -0.5, -0.5);
    modelMatrix = rotation * modelMatrix;
    modelMatrix.translate(0.5, 0.5, 0.5);
  }

  if (display::keys[87]){
    Matrix4 rotation;
    rotation.rotateX(-6);
    modelMatrix.translate(-0.5, -0.5, -0.5);
    modelMatrix = rotation * modelMatrix;
    modelMatrix.translate(0.5, 0.5, 0.5);
  }

  if (display::keys[65]){
    Matrix4 rotation;
    modelMatrix.translate(-0.5, -0.5, -0.5);
    rotation.rotateY(6);
    modelMatrix = rotation * modelMatrix;
    modelMatrix.translate(0.5, 0.5, 0.5);
  }
  if (display::keys[68]){
    Matrix4 rotation;
    modelMatrix.translate(-0.5, -0.5, -0.5);
    rotation.rotateY(-6);
    modelMatrix = rotation * modelMatrix;
    modelMatrix.translate(0.5, 0.5, 0.5);
  }
  if (display::keys[81]){
    Matrix4 rotation;
    rotation.rotateZ(-6);
    modelMatrix.translate(-0.5, -0.5, -0.5);
    modelMatrix = rotation * modelMatrix;
    modelMatrix.translate(0.5, 0.5, 0.5);
  }
  if (display::keys[69]){
    Matrix4 rotation;
    rotation.rotateZ( 6);
    modelMatrix.translate(-0.5, -0.5, -0.5);
    modelMatrix = rotation * modelMatrix;
    modelMatrix.translate(0.5, 0.5, 0.5);
  }

  if (display::keys[32]){
    modelMatrix.identity();
    //modelMatrix.scale(5,5,5);
    //modelMatrix.translate(-1.5, -0.5, 4.0);
  }
}

void Polygon::setup(){
  model.vertexSize = 3;
  model.colorIncluded = false;
  model.load("./models/ct.raw");
  theProgram.build("polygon");
  theProgram.getUniformLocation("modelViewMatrix");

  modelMatrix.identity();

}
