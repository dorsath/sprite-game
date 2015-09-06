#include "config.hpp"

void FBO::create(){

  printf("Creating FBO:...\n");
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1280, 960, 0, GL_RGBA, GL_FLOAT, 0);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


  glFramebufferTexture2D(GL_FRAMEBUFFER,      // 1. fbo target: GL_FRAMEBUFFER 
                       GL_COLOR_ATTACHMENT0,  // 2. attachment point
                       GL_TEXTURE_2D,         // 3. tex target: GL_TEXTURE_2D
                       textureID,             // 4. tex ID
                       0);                    // 5. mipmap level: 0(base)

  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(status != GL_FRAMEBUFFER_COMPLETE)
    printf("FBO NOT DONE\n");
  else
    printf("\tdone\n");
  
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::bind(){
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FBO::unbind(){
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


