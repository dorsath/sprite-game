#version 410
out vec4 outputColor;

in vec2 textureCoords;
uniform sampler2D sprites;

void main() {
  outputColor = texture(sprites, textureCoords);
  //outputColor = vec4(1,1,1,1);
}

