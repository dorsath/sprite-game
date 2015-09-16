#version 410
out vec4 outputColor;

in vec2 textureCoords;
uniform sampler2D sprites;

void main() {
  vec2 texCoords =  vec2(textureCoords.x, (1 - textureCoords.y));// * vec2(1, -1);
  outputColor = texture(sprites, texCoords);
  
  //outputColor = vec4(1,1,1,1);
}

