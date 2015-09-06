#version 410
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
smooth out vec4 theColor;

uniform int mode;

void main(){
  vec3 offset;
  if (mode == 0 || mode == 1){
    offset = vec3(2.0, 2.0, 0.0);
  } else if (mode == 2 || mode == 3){
    offset = vec3(2.0, 0.0, 0.0);
  } else if (mode == 4 || mode == 5){
    offset = vec3(2.0, -2.0, 0.0);
  }
  float scale  = 0.33;
  gl_Position = vec4((position.xyz + offset) * scale, 1.0);
  theColor = color;
}
