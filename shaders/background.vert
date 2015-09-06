#version 410
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 modelViewMatrix;
smooth out vec4 theColor;

void main(){
  gl_Position = modelViewMatrix * position;
  theColor = color;
}

