#version 400

in vec3 position;
in vec3 normal;
in vec2 texCoord;
in vec3 tangent;

uniform int debugOption;

layout (location = 0) out vec4 fColor;

#define M_PI 3.1415926535897932384626433832795

void main(){
	// Modo normales
	if(debugOption == 0){
		fColor = vec4(normal, 1.0);
	}
	// Modo tangentes
	if(debugOption == 1){
		fColor = vec4(tangent, 1.0);
	}
	// Modo coordenadas de textura
	if(debugOption == 2){ 
		fColor = vec4(vec3(texCoord, 1.0), 1.0);
	}
}