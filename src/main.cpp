#include "config.hpp"

int main(void) {

  display::setup();

  //Background* background = new Background;
  //display::add_to_draw(background);

  //Octree octree;
  //octree.load("./textures/octree_ct.raw", 512);

  Text* text = new Text;
  display::add_to_draw(text);

  //Slice* slice_0 = new Slice;
  //slice_0->octree = octree;
  //display::add_to_draw(slice_0);
  //display::Register slice_0_register = {slice_0, 430, 0, 640, 160};
  //display::scrollRegisters.push_back(slice_0_register);

  //Slice* slice_2 = new Slice;
  //slice_2->octree = octree;
  //display::add_to_draw(slice_2);
  //slice_2->mode = 2;
  //display::Register slice_2_register = {slice_2, 430, 160, 640, 320};
  //display::scrollRegisters.push_back(slice_2_register);


  //Slice* slice_4 = new Slice;
  //slice_4->octree = octree;
  //display::add_to_draw(slice_4);
  //slice_4->mode = 4;
  //display::Register slice_4_register = {slice_4, 430, 320, 640, 480};
  //display::scrollRegisters.push_back(slice_4_register);

  //Object* x = new Object;
  //x->octree = octree;
  //display::add_to_draw(x);

  display::draw();

}

