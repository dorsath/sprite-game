#version 410
out vec4 outputColor;
smooth in vec4 theColor;

uniform sampler2D volume;
uniform int octreeTexSize;
uniform int octreeSize;
uniform int mode;
uniform float depth;


void indexToCoord(in int index, out ivec2 coord){
  coord = ivec2(index % octreeTexSize, index / octreeTexSize);
}

void octreeCoord(in vec3 pointer, in int nodeSize, out vec3 coord){
  coord = floor((mod(pointer, (nodeSize * 2)))/ nodeSize);
}

void lookupTree(in int octreeSize, in vec3 pointer, out vec4 color, out int nodeSize, out vec3 nodeRoot){
  int index = 1;
  nodeRoot = vec3(0.0, 0.0, 0.0);

  for (nodeSize = octreeSize; nodeSize > 1; nodeSize = nodeSize / 2){

    vec3 octreeCoordinate;
    octreeCoord(pointer * octreeSize, nodeSize / 2, octreeCoordinate);
    int octreeIndex = int(octreeCoordinate.x) + int(octreeCoordinate.y) * 2 + int(octreeCoordinate.z) * 4;

    nodeRoot += octreeCoordinate * (float(nodeSize) / float(octreeSize)) * 0.5;

    index += octreeIndex;
    ivec2 textureCoord;
    indexToCoord(index, textureCoord);

    float value = texelFetch(volume, textureCoord, 0).a;
    if (value > 1){
      index = int(value);
    } else {
      color = texelFetch(volume, textureCoord, 0);
      break;
    }
  }

}

void main(){
  int nodeSize;
  vec3 nodeRoot;
  vec3 pointer;

  if(theColor.x > 0.955 && theColor.x < 0.96 && theColor.y < depth){
    outputColor = vec4(1.0, 1.0, 1.0, 1.0);
    return;
  }


  if (mode == 0){
    pointer = vec3(theColor.xy, depth);
  } else if (mode == 1){
    pointer = vec3(theColor.xy, 1.0 - depth);
  } else if (mode == 2){
    pointer = vec3(depth, theColor.yx);
  } else if (mode == 3){
    pointer = vec3(1.0 - depth, theColor.yx);
  } else if (mode == 4){
    pointer = vec3(theColor.x, depth, theColor.y);
  } else if (mode == 5){
    pointer = vec3(theColor.x, 1.0 - depth, theColor.y);
  } 
  lookupTree(octreeSize, pointer.xyz, outputColor, nodeSize, nodeRoot);
  //outputColor = theColor * depth;
}

