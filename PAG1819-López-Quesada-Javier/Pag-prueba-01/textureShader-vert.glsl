#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTextCoord;
//layout (location = 3) in vec3 vTangent;

uniform mat4 mModelView;
uniform mat4 mModelViewProj;

out vec3 position;
out vec3 normal;
out vec2 texCoord;

void main() {
	normal = vec3( mModelView * vec4(vNormal, 0.0) );
	position = vec3( mModelView * vec4(vPosition, 1.0) );
	gl_Position = mModelViewProj * vec4(vPosition, 1.0);
	texCoord = vTextCoord;
}