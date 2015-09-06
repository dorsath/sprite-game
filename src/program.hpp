#ifndef PROGRAM_HPP
#define PROGRAM_HPP

class Program {
  public:
    GLuint programID;
    std::map<const char*, GLuint> uniformLocations;

  public:
    void build(const char* name);
    void use();
    GLuint getUniformLocation(const char* name);
    GLuint uniform(const char* name);

};

#endif
