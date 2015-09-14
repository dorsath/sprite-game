#version 410
layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 texCoords;

out vec2 textureCoords;
uniform vec2 position;

void main(){
  gl_Position = vec4((vertex + position) / 8 , 0.5, 1);
  textureCoords = texCoords;
  
}
