#ifndef FBO_HPP
#define FBO_HPP

class FBO {
  public:
    GLuint fbo;
    GLuint textureID;

  public:
    void create();
    void bind();
    void unbind();

};

#endif


