#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vTangent;

uniform mat4 mModelViewProj;

out vec3 position;
out vec3 normal;
out vec2 texCoord;
out vec3 tangent;

void main(){
	gl_Position = mModelViewProj * vec4(vPosition, 1.0);
	position = vPosition;
	normal = vNormal;
	texCoord = vTexCoord;
	tangent = vTangent;
}