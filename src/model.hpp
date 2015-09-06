#ifndef MODEL_HPP
#define MODEL_HPP

class Model {
  public:
    GLuint vao;
    GLuint vbo;
    int size;
    int verticesCount;
    int vertexSize;
    bool colorIncluded;
    void* colorOffset;

  public:
    void load(const char* filepath);
    void create(std::string text);
};

#endif
