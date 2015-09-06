#include <fstream>
#include "octree/octree.h"

int size = 256;
Octree<float> tree(size);

typedef struct Point Point;

struct Point
{
  float value;
  Point *Point;
};

void writeToFile(float* vertexData, long int size, const char* filepath){
  printf("Writing array to %s of size: %lu\n", filepath, size);

  FILE* file;
  file = fopen(filepath, "wb");
  fwrite(vertexData, 4, size, file);

  fclose(file);
}

void createObject(){
  int array_size = size * size * size;
  int cube_root[3] = {32, 32, 32};
  int cube_end[3] = {96, 96, 96};

  for (int i = 0; i < array_size; i += 1){
    int x = i % size;
    int y = (i / size) % size;
    int z = (i / size / size);
    if (
        x - cube_root[0] >= 0 &&
        y - cube_root[1] >= 0 &&
        z - cube_root[2] >= 0 &&

        x - cube_end[0] <= 0 &&
        y - cube_end[1] <= 0 &&
        z - cube_end[2] <= 0)  {
      tree(x,y,z) = 1.0;
    }
  }

  //writeToFile(object, array_size, "textures/cube.raw");

}

void recursiveWalk(Octree<float>::Node* node, int size, int target_size){
  printf("Recursive walk - size: %d of %d\n", size, target_size);
  if (size == target_size){
    return;
  }

  printf("child type:%u\n", node->type());
  switch(node->type()){
    {
      case Octree<float>::BranchNode:
        printf("Branch!\n");
        //Octree<float, 2>::Branch(root);

        for (int i = 0; i < 8; i += 1){
            Octree<float, 1>::Node* child = reinterpret_cast<Octree<float>::Branch*>(node)->child(i);
            recursiveWalk(child, size / 2, target_size);
        }
        //root_ = new Branch   ( *reinterpret_cast<Branch   *>(o.root_) );
        break;
    }
    case Octree<float>::LeafNode:
      printf("Leaf!\n");
      //root_ = new Leaf     ( *reinterpret_cast<Leaf     *>(o.root_) );
      break;
    case Octree<float>::AggregateNode:
      printf("Aggregate node?!\n");
      //root_ = new Aggregate( *reinterpret_cast<Aggregate*>(o.root_) );
      break;
  }
}

void secondRecursive(Octree<float>::Branch& b){
  for ( int i = 0; i < 8; ++i ) {
      if ( b.child(i) ) {
          switch ( b.child(i)->type() ) {
            case Octree<float>::BranchNode:
                  Octree<float>::Branch new_branch = new Octree<float>::Branch(
                          *reinterpret_cast<const Octree<float>::Branch   *>(b.child(i)) );
                  //secondRecursive(new_branch);
                  break;
            case Octree<float>::LeafNode:
                  new Octree<float>::Leaf(
                          *reinterpret_cast<const Octree<float>::Leaf     *>(b.child(i)) );
                  break;
            case Octree<float>::AggregateNode:
                  new Octree<float>::Aggregate(
                          *reinterpret_cast<const Octree<float>::Aggregate*>(b.child(i)) );
                  break;
          }
      }
  }

}

int main(){
  createObject();
  Octree<float>::Node* root = tree.root();
  Octree<float>::Branch root_branch = 
        *reinterpret_cast<const Octree<float>::Branch   *>(root);
  secondRecursive(root_branch);
  //int result = tree.nodesAtSize(32);
  //printf("Size: %d\n", result);
  return 0;

}
