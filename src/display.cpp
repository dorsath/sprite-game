#include "config.hpp"

namespace display {
  GLFWwindow* window;

  std::vector<Drawable*> drawable_objects;
  boost::tuple<int, int> mouseCoords;
  std::vector<Register> scrollRegisters;

  int keys[348];
  Matrix4 perspectiveMatrix;
  Matrix4 viewMatrix;
  GLuint MVPMatrixUnif;
  Coordinate mouseCoord;

  float fFrustumScale = 1.0f;
  float fzNear = 0.1f;
  float fzFar = 100.0f;

  float lightPos[3] = {0.0f, 5.0f, 0.0f};

  void error_callback(int error, const char* description)
  {
      fputs(description, stderr);
  }

  void mouse_pos_callback(GLFWwindow* window, double x, double y){
    display::mouseCoord.x = int(x);
    display::mouseCoord.y = int(y);
  }

  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    for (int i = 0; i < scrollRegisters.size(); i += 1) {
      if (
      mouseCoord.x >= scrollRegisters[i].low_x &&
      mouseCoord.x <= scrollRegisters[i].high_x &&
      mouseCoord.y >= scrollRegisters[i].low_y &&
      mouseCoord.y <= scrollRegisters[i].high_y) {
        scrollRegisters[i].model->scroll_callback(yoffset);
      }
    }
  }

  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    if (action == 1)
      keys[key] = 1;
    if (action == 0)
      keys[key] = 0;
  }

  GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile)
  {
      GLuint shader = glCreateShader(eShaderType);
      std::string line,text;
      std::ifstream in("shaders/" + strShaderFile);
      while(std::getline(in, line))
      {
          text += line + "\n";
      }
      const char *strFileData = text.c_str();
      glShaderSource(shader, 1, &strFileData, NULL);
      glCompileShader(shader);
      GLint status;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
      if (status == GL_FALSE)
      {
          GLint infoLogLength;
          glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
          GLchar *strInfoLog = new GLchar[infoLogLength + 1];
          glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
          const char *strShaderType = NULL;
          switch(eShaderType)
          {
          case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
          //case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
          case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
          }
          fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
          delete[] strInfoLog;
      }
   return shader;
  }

  void BuildProgram(const char* shader, GLuint* program){
    char name[50];
    std::vector<GLuint> shaderList;

    sprintf(name, "%s.vert", shader);
    shaderList.push_back(display::CreateShader(GL_VERTEX_SHADER, name));
    sprintf(name, "%s.frag", shader);
    shaderList.push_back(display::CreateShader(GL_FRAGMENT_SHADER, name));

    *program = display::CreateProgram(shaderList);
    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
  }

  GLuint CreateProgram(const std::vector<GLuint> &shaderList)
  {
      GLuint program = glCreateProgram();
      for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
       glAttachShader(program, shaderList[iLoop]);
      glLinkProgram(program);
      GLint status;
      glGetProgramiv (program, GL_LINK_STATUS, &status);
      if (status == GL_FALSE)
      {
          GLint infoLogLength;
          glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
          GLchar *strInfoLog = new GLchar[infoLogLength + 1];
          glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
          fprintf(stderr, "Linker failure: %s\n", strInfoLog);
          delete[] strInfoLog;
  }
      for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
          glDetachShader(program, shaderList[iLoop]);
      return program;
  }


  void setup(){
    glfwSetErrorCallback(error_callback);
    
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window,reshape);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_pos_callback);

    check_error("Error during setup");

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    perspectiveMatrix[0] = fFrustumScale / (width / (float)height);
    perspectiveMatrix[5] = fFrustumScale;
    perspectiveMatrix[10] = (-fzFar - fzNear) / (fzNear - fzFar);
    perspectiveMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
    perspectiveMatrix[11] = 1.0f;

    viewMatrix.identity();
    viewMatrix.translate(0, 0, -5);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);

    check_error("Error after setup");

  }

  bool check_error(const char* error_message){
    GLint error = glGetError();
    if (error != GL_NO_ERROR){
      printf("%s: %d\n", error_message, error);
      return true;
    }
    return false;
  }

  void add_to_draw(Drawable* object){
    check_error("Error before setup of object");
    drawable_objects.push_back(object);
    drawable_objects[drawable_objects.size() - 1]->setup();

    check_error("Error during setup of object");
  }

  void reshape(GLFWwindow* window, int w, int h) {
      perspectiveMatrix[0] = fFrustumScale / (w / (float)h);
      perspectiveMatrix[5] = fFrustumScale;
      glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  }


  void draw(){

    while (!glfwWindowShouldClose(window)) {
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClearDepth(1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      if (keys[83]){
        viewMatrix.translate(0, 0, -0.1);
      }
      if (keys[87]){
        viewMatrix.translate(0, 0, 0.1);
      }

      if (keys[65]){
        viewMatrix.translate( 0.1, 0, 0);
      }
      if (keys[68]){
        viewMatrix.translate(-0.1, 0, 0);
      }

      if (keys[72]){
        lightPos[0] -= 0.1;
      }

      if (keys[74]){
        lightPos[2] -= 0.1;
      }

      if (keys[75]){
        lightPos[2] += 0.1;
      }

      if (keys[76]){
        lightPos[0] += 0.1;
      }

      if (keys[73]){
        lightPos[1] -= 0.1;
      }

      if (keys[85]){
        lightPos[1] += 0.1;
      }


      for (int i = 0; i < drawable_objects.size(); i = i + 1) {
        drawable_objects[i]->draw();
      }


      if (check_error("Error during drawing")){
        break;
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
  }
}
