#version 410
out vec4 outputColor;

uniform sampler2D sprites;
smooth in vec2 texcoords;

void main(){
  outputColor = texture(sprites, texcoords);

}



