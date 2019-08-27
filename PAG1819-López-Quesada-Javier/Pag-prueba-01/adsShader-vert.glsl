#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

uniform mat4 mModelView;
uniform mat4 mModelViewProj;

out vec3 position;
out vec3 normal;

void main() {
	normal = vec3( mModelView * vec4(vNormal, 0.0) );
	position = vec3( mModelView * vec4(vPosition, 1.0) );
	gl_Position = mModelViewProj * vec4(vPosition, 1.0);
}