#version 410
layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 color;

uniform mat4 modelViewMatrix;
out vec3 inputColor;

void main(){
  gl_Position = modelViewMatrix * vec4(position, 1);
  inputColor = position;
}

