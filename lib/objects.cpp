#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>



void writeToFile(float* vertexData, long int size){
  const char* path = "models/square.raw";
  printf("model file: %s at size: %lu\n", path, size);

  FILE* file;
  file = fopen("models/square.raw", "wb");
  fwrite(vertexData, 4, size, file);

  fclose(file);

}

int main(){

  float vertices[] = {
     1.0f, -1.0f,  0.0f,   1.0f,
     1.0f,  1.0f,  0.0f,   1.0f,
    -1.0f,  1.0f,  0.0f,   1.0f,
    -1.0f, -1.0f,  0.0f,   1.0f,

    //-0.5f, -0.5f, -0.5f,   1.0f, 
    // 0.5f, -0.5f, -0.5f,   1.0f, 
    // 0.5f,  0.5f, -0.5f,   1.0f, 
    //-0.5f,  0.5f, -0.5f,   1.0f, 

    //-0.5f, -0.5f,  0.5f,   1.0f, 
    // 0.5f, -0.5f,  0.5f,   1.0f, 
    // 0.5f,  0.5f,  0.5f,   1.0f, 
    //-0.5f,  0.5f,  0.5f,   1.0f, 
  };

  float colors[] = {
     1.0f,  0.0f,  0.0f,   1.0f,
     1.0f,  1.0f,  0.0f,   1.0f,
     0.0f,  1.0f,  0.0f,   1.0f,
     0.0f,  0.0f,  0.0f,   1.0f,
    //0.0f, 0.0f, 0.0f,  1.0f, 
    //1.0f, 0.0f, 0.0f,  1.0f, 
    //1.0f, 1.0f, 0.0f,  1.0f, 
    //0.0f, 1.0f, 0.0f,  1.0f, 

    //0.0f, 0.0f, 1.0f,  1.0f, 
    //1.0f, 0.0f, 1.0f,  1.0f, 
    //1.0f, 1.0f, 1.0f,  1.0f, 
    //0.0f, 1.0f, 1.0f,  1.0f, 
  };

  int indices[] = { 
    0, 1, 2, 0, 2, 3, //front
    //4, 5, 1, 4, 1, 0, //bottom
    //2, 6, 7, 2, 7, 3,  //top
    //5, 4, 7, 5, 7, 6, //back
    //4, 0, 3, 4, 3, 7, //left
    //1, 5, 6, 1, 6, 2 //right
  };

  long int size = sizeof(indices)/sizeof(*indices);

  float vertexData[size * 4];
  float colorData[size * 4];
  for (int i = 0; i < size; i += 1){
    if (i % 3 == 0){
      printf("---\n");
    }
    for (int n = 0; n < 4; n += 1){
      float point = vertices[indices[i] * 4 + n];
      vertexData[i * 4 + n] = point;
      colorData[i * 4 +n] = colors[indices[i] * 4 + n];
      printf("%f,", point);
    }
    printf("\n");
  }

  float totalData[size * 4 * 2];
  memcpy(totalData, vertexData, size * 4 * sizeof(float));
  memcpy(totalData + size * 4, colorData, size * 4 * sizeof(float));

  printf("size: %lu\n", size);

  writeToFile(totalData, size * 2 * 4);

  return 0;
}
