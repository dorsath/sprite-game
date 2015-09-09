#version 410
out vec4 outputColor;

in vec2 textureCoords;
uniform sampler2D sprites;

void main() {
  outputColor = vec4(texture(sprites, textureCoords).xy, 0, 0.0);
  //outputColor = vec4(1,1,1,1);
}

