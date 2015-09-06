#ifndef OCTREE_HPP
#define OCTREE_HPP

class Octree {
  public:
    int length;
    int resolution;
    GLuint textureID;
    void load(const char* filepath, int set_resolution);

};
#endif


