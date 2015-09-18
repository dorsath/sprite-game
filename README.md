Sprite game
===========

A sprite game in progress built from ground with GLFW & OpenGL.

Why
---

I wanted to apply my acquired knowledge on shaders
After endlessly focusing on 3d algorithms to view volumetric data I wanted to focus on other aspects of making a game.
This is all of course WIP and just for experimentation.


Prerequisites
-------------

* GLFW3
* Clang (I'm using v6.1.0)

How to use
----------

###Game

To build and start the game: 
`make`

Use WASD to walk around. 

###Chunk builder:

To edit the map:
`make cb`

Right click  to select a sprite. Left click on the sprite to select it and click or drag an area in the chunk to place it.
Space saves it to file. You can then walk around in that chunk in the game.
To navigate between chunks use the arrow keys.
