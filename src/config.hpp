#ifndef CONFIG_HPP
#define CONFIG_HPP

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "boost/tuple/tuple.hpp"
#include <map>
#include "../lib/Matrices.h"
#include "../lib/lodepng.h"
#include <stdio.h>

//My src
#include "coordinate.h"
#include "model.hpp"
#include "octree.hpp"
#include "fbo.hpp"
#include "font.hpp"
#include "program.hpp"
#include "drawable.hpp"

//Drawables
#include "sprite.hpp"
#include "text.hpp"
#include "chunk.hpp"

#include "display.hpp"


#endif
