#version 410
layout(location = 0) in vec2 vertex;

out vec2 vertexCoords;
uniform vec2 position;

void main(){
  gl_Position = vec4((vertex + position) / 8 , 0.5, 1);
  vertexCoords = vertex;
  
}

