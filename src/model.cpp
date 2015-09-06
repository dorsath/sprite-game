#include "config.hpp"

void Model::load(const char* filepath){

  printf("Loading model:%s...\n", filepath);
  FILE* file;
  float buffer;
  file = fopen(filepath, "rb");

  fseek(file, 0L, SEEK_END);
  int size = ftell(file) / sizeof(float);
  fseek(file, 0L, SEEK_SET);
  printf("size: %d\n", size);
  verticesCount = size / vertexSize;
  if (colorIncluded) {
    verticesCount = verticesCount / 2;
    colorOffset = (void*)(verticesCount * vertexSize * sizeof(buffer));
  }
  printf("\tFound %d vertices\n", verticesCount);

  float* vertices = new float[size];
  for (int i = 0; i < size; i += 1){
    fread((void*)(&vertices[i]), sizeof(buffer), 1, file);
  }

  fclose(file);

  printf("\tCreating buffers\n");

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(buffer), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  printf("\tCleaning up\n");
  delete vertices;

  printf("\tDone\n");

}

void Model::create(std::string text){
  std::vector<float> vertices;
  int i = 0;
  for(char& c : text) {
    //std::cout << (int)c << std::endl;

    float x_offset = i;

    float newVertices[12] = {
      x_offset    , 0,
      x_offset + 1, 1,
      x_offset    , 1,

      x_offset    , 0,
      x_offset + 1, 0,
      x_offset + 1, 1
    };

    vertices.insert(vertices.end(), newVertices, newVertices + 12);
    i += 1;
  }

  verticesCount = vertices.size();

  for(char& c : text) {
    int code = (int) c;
    code -= 32;

    float character[2] = { float(code % 16), float(code/16) };
    for (int i = 0; i < 6; ++i)
      vertices.insert(vertices.end(), character, character + 2);
  }


  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

}


