#include "/Users/ronald/Projects/cpp/octree/src/octree.hpp"
#include <fstream>
#include <vector>
#include "ct.cpp"

using namespace::std;

struct Vertex {
  float x, y, z;
};

typedef vector<Vertex> Vertices;

Vertices vertices;

void scaleAndTranslateVertex(Vertex* vertex, int x, int y, int z, float scale){
  vertex->x = float(vertex->x + x) * scale;
  vertex->y = float(vertex->y + y) * scale;
  vertex->z = float(vertex->z + z) * scale;
}

Vertices marchingTetrahedrons(int i){
  int setup = 0;
  Vertices newVertices;

  if (i & (1 << 0)) {
    setup ^= 1;
    setup ^= 4;
    setup ^= 16;
  }
  if (i & (1 << 1)) {
    setup ^= 1;
    setup ^= 2;
    setup ^= 32;
  }

  if (i & (1 << 2)) {
    setup ^= 2;
    setup ^= 4;
    setup ^= 8;
  }

  if (i & (1 << 3)) {
    setup ^= 8;
    setup ^= 16;
    setup ^= 32;
  }
  //printf("setup %d: %d\n", i, setup);

  int n = 0;
  for (int x = 0; x < 6; x += 1){
    if (setup & (1 << x)){
      Vertex v = vertices[x];
      newVertices.push_back(v);
      //printf("%d",x);
      if (n > 2){
        newVertices.push_back(newVertices[0]);
        newVertices.push_back(newVertices[1]);
      }

      n += 1;
    }

  }

  //printf("\n");
  //for(Vertices::iterator it = newVertices.begin() ; it != newVertices.end(); ++it){
  //  //printf("%.2f %.2f %.2f\n", it->x, it->y, it->z);
  //}
  return newVertices;
}

int main(){
  int resolution = 512;
  

  Vertex a = {0, 0, 0.5};
  vertices.push_back(a);
  Vertex b = {0.5, 0.0, 0.5};
  vertices.push_back(b);
  Vertex c = {0.5, 0.0, 0.0};
  vertices.push_back(c);
  Vertex d = {1.0, 0.5, 0.0};
  vertices.push_back(d);
  Vertex e = {0.5, 0.5, 0.0};
  vertices.push_back(e);
  Vertex f = {0.5, 0.5, 0.5};
  vertices.push_back(f);

  marchingTetrahedrons(1);
  marchingTetrahedrons(8);

  const char* filepath = "./textures/octree_ct.raw";
  Octree octree = ct_to_octree(filepath, resolution);
  int x = 0;
  int y = 0;
  int z = 0;

  FILE* file;
  filepath = "./models/ct.raw";
  file = fopen(filepath, "wb");

  float scale = 1.0/resolution;
  int size = pow(octree.resolution,3) - 512 * 512; //dont go into the last row
  for (int i = 0; i < size; i += 1){
    int setup = 0;
    if (octree.filled(x, y, z)) //0
      setup |= 1;
    if (octree.filled(x, y, z + 1)) //1
      setup |= 2;
    if (octree.filled(x + 1, y, z)) //2
      setup |= 4;
    if (octree.filled(x + 1, y + 1, z))
      setup |= 8;

    Vertices newVertices = marchingTetrahedrons(setup);
    for(Vertices::iterator vertex = newVertices.begin(); vertex != newVertices.end(); ++vertex){
      scaleAndTranslateVertex(&(*vertex),x,y,z, scale);

      float vert[3];
      vert[0] = vertex->x;
      vert[1] = vertex->y;
      vert[2] = vertex->z;
      
      fwrite(vert, 4, 3, file);
      //printf("%.2f %.2f %.2f\n", it->x, it->y, it->z);
    }


    x += 1;
    if (x > 511){
      x = 0;
      y += 1;
    }
    if (y > 511){
      y = 0;
      z += 1;
      printf("z: %2d\n", z);
    }
  }
  fclose(file);



  return 0;
}
