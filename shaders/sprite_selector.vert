#version 410
layout(location = 0) in vec2 position;
smooth out vec2 texcoords;

void main(){
  gl_Position = vec4(position, 0, 1);
  texcoords = (position + 1) / 2;
}
