#version 410
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 character;
//layout(location = 1) in vec3 color;

//uniform mat4 modelViewMatrix;
out vec2 inputPosition;
out vec2 inputCharacter;

void main(){
  gl_Position = vec4(position / 10, 0, 1);
  inputPosition = position;
  inputCharacter = character;
}


