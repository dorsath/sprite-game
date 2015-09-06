#include "config.hpp"

void Object::draw(){
  if (display::keys[44]){
    if (density > 0.05)
      density = density * 0.9;
    std::cout << density << std::endl;
  }
  if (display::keys[46]){
    if (density < 0.95)
      density = density * 1.1;
    std::cout << density << std::endl;
  }
  if (display::keys[83]){
    Matrix4 rotation;
    rotation.rotateX(6);
    modelMatrix = modelMatrix * rotation;
  }

  if (display::keys[87]){         
    Matrix4 rotation;
    rotation.rotateX(-6);
    modelMatrix = modelMatrix * rotation;
  }

  if (display::keys[65]){
    Matrix4 rotation;
    rotation.rotateY(6);
    modelMatrix = modelMatrix * rotation;
  }
  if (display::keys[68]){
    Matrix4 rotation;
    rotation.rotateY(-6);
    modelMatrix = modelMatrix * rotation;
  }
  if (display::keys[81]){
    Matrix4 rotation;
    rotation.rotateZ(-6);
    modelMatrix = modelMatrix * rotation;
  }
  if (display::keys[69]){
    Matrix4 rotation;
    rotation.rotateZ( 6);
    modelMatrix = modelMatrix * rotation;
  }

  if (display::keys[32]){
    modelMatrix.identity();
    modelMatrix.scale(5,5,5);
    modelMatrix.translate(-1.5, -0.5, 4.0);
  }


  GLuint unif;

  fbo.bind();
  backProgram.use();
    glBindVertexArray(cube.vao);
    glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glCullFace(GL_FRONT);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)576);
    glUniformMatrix4fv(backProgram.uniform("modelViewMatrixUnif"), 1, GL_FALSE, (display::perspectiveMatrix * modelMatrix ).get());
    glDrawArrays(GL_TRIANGLES, 0, cube.verticesCount);

    glDisableVertexAttribArray(0);
  glUseProgram(0);
  fbo.unbind();


  distance.bind();
  glClear(GL_COLOR_BUFFER_BIT);
  distanceProgram.use();
    glUniform1f(distanceProgram.uniform("density"), density);

    glUniform1i(distanceProgram.uniform("volume"), 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  octree.textureID);

    glUniform1i(distanceProgram.uniform("backface"), 1);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,  fbo.textureID);

    glBindVertexArray(cube.vao);
    glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glCullFace(GL_BACK);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)576);

    glUniformMatrix4fv(distanceProgram.uniform("modelViewMatrix"), 1, GL_FALSE, (display::perspectiveMatrix * modelMatrix ).get());
    glDrawArrays(GL_TRIANGLES, 0, cube.verticesCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
  glUseProgram(0);
  distance.unbind();

  theProgram.use();
    glUniform1i(theProgram.uniform("volume"), 0);

    glUniform1i(theProgram.uniform("backFace"), 1);

    glUniform1i(theProgram.uniform("distanceFace"), 2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  octree.textureID);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,  fbo.textureID);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,  distance.textureID);

    glBindVertexArray(cube.vao);
    glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glCullFace(GL_BACK);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)576);


    glUniformMatrix4fv(theProgram.uniform("modelViewMatrix"), 1, GL_FALSE, (display::perspectiveMatrix * modelMatrix ).get());
    glDrawArrays(GL_TRIANGLES, 0, cube.verticesCount);

    glDisableVertexAttribArray(0);
  glUseProgram(0);
}

void Object::loadTexture(const char* filepath){
  printf("Loading texture:%s...", filepath);

  FILE* file;
  float buffer;

  int size = 64;
  int array_size = size * size * size;

  float* volumeData = new float[array_size];

  file = fopen(filepath, "rb");
  for (int i = 0; i < array_size; i += 1){
    fread((void*)(&volumeData[i]), sizeof(buffer), 1, file);
  }
  fclose(file);

  delete volumeData;
  printf("done\n");
}



void Object::createTexture(GLuint *id){
  int length = 1;
  float volumeData[4] = {0, 1, 0, 1};
  glGenTextures(1, id);
  glBindTexture(GL_TEXTURE_2D, *id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, length, length, 0, GL_RGBA, GL_FLOAT, volumeData);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Object::setup(){

  cube.load("./models/cube.raw");

  //loadModel("./models/cube.raw");

  theProgram.build("octree");
  backProgram.build("back");
  distanceProgram.build("distance");

  theProgram.use();

  modelMatrix.identity();
  modelMatrix.scale(5,5,5);
  modelMatrix.translate(-1.5, -0.5, 4.0);

  theProgram.getUniformLocation("volume");
  theProgram.getUniformLocation("backFace");
  theProgram.getUniformLocation("distanceFace");
  theProgram.getUniformLocation("modelViewMatrix");
  theProgram.getUniformLocation("depth");
  distanceProgram.getUniformLocation("modelViewMatrix");
  distanceProgram.getUniformLocation("volume");
  distanceProgram.getUniformLocation("backFace");
  distanceProgram.getUniformLocation("density");

  float fFrustumScale = 1.0f;
  float fzNear = 0.5f;
  float fzFar  = 10.0f;
  density = 0.5;

  perspectiveMatrix[0]  = fFrustumScale;
  perspectiveMatrix[5]  = fFrustumScale;
  perspectiveMatrix[10] = (-fzFar - fzNear) / (fzNear - fzFar);
  perspectiveMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
  perspectiveMatrix[11] = 1.0f;



  GLuint unif = theProgram.getUniformLocation("octreeTexSize");
  glUniform1i(unif, octree.length);
  unif = distanceProgram.getUniformLocation("octreeTexSize");
  glUniform1i(unif, octree.length);

  unif = theProgram.getUniformLocation("octreeSize");
  glUniform1i(unif, octree.resolution);
  unif = distanceProgram.getUniformLocation("octreeSize");
  glUniform1i(unif, octree.resolution);

  fbo.create();
  distance.create();

  glUseProgram(0);

}

