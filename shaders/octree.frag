#version 410
out vec4 outputColor;
smooth in vec4 theColor;
in vec4 vertexPoint;

uniform sampler2D volume;
uniform sampler2D backFace;
uniform sampler2D distanceFace;

uniform mat4 modelViewMatrix;
uniform int octreeTexSize;
uniform float depth;
uniform int octreeSize;

struct Face {
  vec3 point;
  vec3 normal;
};

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

void aabb(in vec3 root, in vec3 rayDir, in float nodeSize, in vec3 nodeRoot, out float distance){
  //node root is in bottom corner, so 0, 0, 0.
  Face face;
  float closest = 999999999;

  for (int faceIndex = 0; faceIndex < 6; faceIndex += 1){
    float m = float(floor(faceIndex / 3));
    face.point  = vec3(m, m, m) * nodeSize + nodeRoot;
    face.normal = vec3(
        float(floor(mod((0 + faceIndex), 3) / 2)),
        float(floor(mod((1 + faceIndex), 3) / 2)),
        float(floor(mod((2 + faceIndex), 3) / 2))
        );

    float denominator = dot(face.normal, rayDir);
    if (denominator == 0.0){
      continue;
    }
    vec3 p3_1 = (face.point - root);

    distance = dot(face.normal,p3_1) / denominator;

    vec3 new_point = root + (distance - 0.00001) * rayDir;

    if (distance < 0.0){
      continue;
    }

    if (
      new_point.x >= nodeRoot.x &&
      new_point.y >= nodeRoot.y &&
      new_point.z >= nodeRoot.z &&
      new_point.x <= nodeRoot.x + nodeSize &&
      new_point.y <= nodeRoot.y + nodeSize &&
      new_point.z <= nodeRoot.z + nodeSize){

      if (distance < closest){
        closest = distance;
      }
    }
  }


  distance = closest;

}
void main(){
  //outputColor = theColor;
  outputColor = vec4(0, 0, 0, 1);
  vec2 textureCoords = vec2(gl_FragCoord.x / 1280, gl_FragCoord.y / 960);
    //outputColor = vec4(textureCoords.xy, 0, 1);
  float stepsize = 0.01;
  
  vec4 rayDir   = normalize(texture(backFace, textureCoords) - theColor);
  int nodeSize;
  vec3 nodeRoot;
  float distance = texture(distanceFace, textureCoords).r;
  vec4 pointer  = theColor + distance * rayDir;

  vec4 lightDir = vec4(-1, -1, 0, 1);

  float distribution[5];
  distribution[0] = 0.0359;
  distribution[1] = 0.2384;
  distribution[2] = 0.4514;
  distribution[3] = 0.2384;
  distribution[4] = 0.0359;


  if (distance < 0.01){
    discard;
  }

  //outputColor = vec4(distance * distance, 0, 0, 1);
  //return;
  int dd = 1;
  ivec2 absPointer = ivec2(gl_FragCoord.xy);

  float null_point = texelFetch(distanceFace, absPointer + ivec2(1,0),0).r;

  float dx = 0.0;
  for (int i = -2; i <= 2; i += 1){
    dx += (null_point - texelFetch(distanceFace, absPointer + ivec2(i,0),0).r) * distribution[i + 2];
  }


  null_point = texelFetch(distanceFace, absPointer + ivec2(0,1),0).r;
  float dy = 0.0;
  for (int i = -2; i <= 2; i += 1){
      dy += (null_point - texelFetch(distanceFace, absPointer + ivec2(0,i),0).r) * distribution[i + 2];
  }

  float sign = dx / abs(dx);
  float off = 0.002;//1280; //eyeballed this number
  vec3 norm = normalize(vec3(
      dx,
      dy,
      off * sign));

  //outputColor = vec4(-sign, 0, 0, 1);
  lookupTree(octreeSize, pointer.xyz, outputColor, nodeSize, nodeRoot);
  outputColor = outputColor * (1 - dot(vec4(norm, 1), lightDir) / 2);
}
