#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object: public Drawable{
public:
  Model cube;
  FBO fbo;
  FBO distance;
  //
  Octree octree;
  //programs
  Program theProgram;
  Program backProgram;
  Program distanceProgram;

  //Uniform values
  Matrix4 modelMatrix;
  Matrix4 perspectiveMatrix;

  //Texture
  GLuint textureID;
  GLuint fboTextureId;

  float density;

  void draw();
  void setup();
  void loadModel(const char* filepath);
  void loadTexture(const char* filepath);
  void loadOctree(const char* filepath);
  void createProgram(const char* shader, GLuint *program);
  void createFBO();
  void createTexture(GLuint *unif);


private:
  struct Face {
    float point[3];
    float normal[3];
  };
};

#endif
