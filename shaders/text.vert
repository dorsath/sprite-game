#version 410
layout(location = 0) in vec2 vertex;
//layout(location = 1) in vec3 color;

uniform vec2 position;
out vec2 inputPosition;

void main(){
  gl_Position = vec4((vertex / 20) + position, 0.0, 1);
  inputPosition = vertex;
}


