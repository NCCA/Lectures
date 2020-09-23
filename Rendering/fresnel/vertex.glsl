#version 300 es
// Based on https://learnopengl.com/PBR/Theory

precision highp float;
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

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
  TexCoords=uv;  
  gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
}
