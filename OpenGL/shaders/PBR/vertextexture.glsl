#version 300 es
// Based on https://learnopengl.com/PBR/Theory
// textures from https://freepbr.com/
precision highp float;
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 textureRotation;
uniform vec2 textureRepeat;
in vec3 position;
in vec3 normal;
in vec2 uv;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

void main()
{
  WorldPos = vec3(modelMatrix * vec4(position, 1.0f));
  Normal=normalMatrix*normal;
  TexCoords=mat2(textureRotation)*(uv*textureRepeat);  
  gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
}
