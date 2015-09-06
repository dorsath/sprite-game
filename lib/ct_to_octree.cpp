#include "ct.cpp"

int main(){
  const char* filepath = "./textures/octree_ct.raw";
  Octree octree = ct_to_octree(filepath, 512);
  octree.to2DTexture();
  octree.writeToFile(filepath);
  return 0;
}

