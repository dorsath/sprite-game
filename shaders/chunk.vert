#version 410
layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 texCoords;

out vec2 textureCoords;

void main(){
  gl_Position = vec4((vertex / 16) + vec2(-1, -1), 0.5, 1);
  textureCoords = texCoords;
  
}
