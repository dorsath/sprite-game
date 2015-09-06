#include "config.hpp"

void Slice::draw(){
  if (display::keys[45] && depth < 0.98){
    depth += 0.01;
    std::cout << depth << std::endl;
  }
  if (display::keys[61] && depth > 0.02){
    depth -= 0.01;
    std::cout << depth << std::endl;
  }

  //if (display::keys[48]){ //up
  //  mode = 0;
  //}
  //if (display::keys[49]){ //down
  //  mode = 1;
  //}
  //if (display::keys[50]){ //left
  //  mode = 2;
  //}
  //if (display::keys[51]){ //right
  //  mode = 3;
  //}
  //if (display::keys[52]){ //z_in
  //  mode = 4;
  //}
  //if (display::keys[53]){ //z_in
  //  mode = 5;
  //}

  sliceProgram.use();
    glUniform1i(mode_unif, mode);
    glUniform1f(depth_unif, depth);
    glUniform1i(octree_unif, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  octree.textureID);

    glBindVertexArray(square.vao);
    glBindBuffer(GL_ARRAY_BUFFER, square.vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)96);
    glDrawArrays(GL_TRIANGLES, 0, square.verticesCount);

    glDisableVertexAttribArray(0);
  glUseProgram(0);
  
}

void Slice::scroll_callback(double yoffset){
  float value = float(yoffset/400);
  if (depth + value > 0.01 && depth + value < 0.99){
    depth += value;
  }
}

void Slice::setup(){
  depth = 0.50;
  mode = 0;

  square.load("./models/square.raw");
  sliceProgram.build("slice");

  octree_unif     = sliceProgram.getUniformLocation("volume");
  depth_unif      = sliceProgram.getUniformLocation("depth");
  mode_unif       = sliceProgram.getUniformLocation("mode");


  //octree.load("./textures/octree_wood.raw", 1024);
  GLuint unif = sliceProgram.getUniformLocation("octreeTexSize");
  GLuint octreeSizeUnif  = sliceProgram.getUniformLocation("octreeSize");
  glUniform1i(unif, octree.length);
  glUniform1i(octreeSizeUnif, octree.resolution);
}
