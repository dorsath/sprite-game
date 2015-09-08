#ifndef DISPLAY_HPP
#define DISPLAY_HPP

namespace display {
  extern GLuint theProgram;
  extern GLuint vertexBufferObject;
  extern GLuint vao;
  extern Coordinate mouseCoord;

  struct Register {
    Drawable* model;
    int low_x;
    int low_y;
    int high_x;
    int high_y;
  };

  extern Coordinate windowSize;

  extern std::vector<Register> scrollRegisters;
  extern std::vector<Register> clickRegisters;
  void error_callback(int error, const char* description);
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);

  void BuildProgram(const char* shader, GLuint* program);
  GLuint CreateProgram(const std::vector<GLuint> &shaderList);
  void setup();
  void draw();
  void reshape(GLFWwindow* window, int w, int h);
  void add_to_draw(Drawable* object);
  bool check_error(const char* error_message);

  extern GLuint MVPMatrixUnif;
  extern Matrix4 perspectiveMatrix;
  extern Matrix4 viewMatrix;
  extern int keys[348];

  extern float fFrustumScale;
  extern float fzNear;
  extern float fzFar;

  extern float lightPos[3];

}
#endif
