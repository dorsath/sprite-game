#version 410
layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 character;
//layout(location = 1) in vec3 color;

uniform vec2 position;
uniform int lineNr;
out vec2 inputPosition;
out vec2 inputCharacter;

void main(){
  gl_Position = vec4(((vertex + vec2(0, -float(lineNr))) / 40) + position, 0, 1);
  inputPosition = vertex;
  inputCharacter = character;
}


