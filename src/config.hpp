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

//My libs
#include "coordinate.h"
#include "model.hpp"
#include "octree.hpp"
#include "fbo.hpp"
#include "font.hpp"
#include "program.hpp"
#include "drawable.hpp"
#include "texture.hpp"

//Drawables
#include "drawables/sprite.hpp"
#include "drawables/text.hpp"
#include "drawables/chunk.hpp"
#include "drawables/player.hpp"
#include "drawables/item.hpp"

#include "display.hpp"


#endif
