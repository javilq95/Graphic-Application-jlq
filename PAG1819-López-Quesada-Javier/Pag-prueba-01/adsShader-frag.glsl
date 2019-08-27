#version 400
#define M_PI 3.1415926535897932384626433832795

in vec3 position;
in vec3 normal;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform vec3 positionL;
uniform vec3 direction;
uniform float exponent;
uniform float cosAngle;
uniform float at1;
uniform float at2;
uniform float at3;

uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;

uniform int modeLight;

layout (location = 0) out vec4 FragColor;

vec4 ambient() {
	return vec4(Ia, 1.0);
}

float attenuation(float dist) {
	return min( 1.0 / (at1 + at2 * dist + at3 * dist * dist), 1.0 );
}

vec4 puntual() {
	vec3 n;
	
	if (gl_FrontFacing) {
		n = normalize(normal);
	} else {
		n = normalize(-normal);
	}

	vec3 l = normalize(positionL - position);
	vec3 v = normalize(-position);
	vec3 r = reflect(-l, n);
		
	vec3 diffuse = (Id * Kd * max( dot(l,n), 0.0));
	vec3 specular;

	if (dot(l, n) < 0.0) {
		specular = vec3(0.0);
	} else {
		specular = (Is * Ks * pow( max( dot(r,v), 0.0), shininess ));
	}

	return vec4( attenuation( distance(position, positionL) ) * (diffuse + specular), 1.0);
}

vec4 spot() {
	vec3 n;
	
	if (gl_FrontFacing) {
		n = normalize(normal);
	} else {
		n = normalize(-normal);
	}

	vec3 l = normalize(positionL - position);
	vec3 v = normalize(-position);
	vec3 r = reflect(-l, n);

	float spotFactor = 0.0;

	if (dot(-l, direction) > cosAngle) { 
		spotFactor = pow(dot(-l, direction), exponent) ; 
	}

	vec3 diffuse = (Id * Kd * max( dot(l,n), 0.0));

	vec3 specular;

	if (dot(l, n) < 0.0) {
		specular = vec3(0.0);
	} else {
		specular = (Is * Ks * pow( max( dot(r,v), 0.0), shininess) );
	}

	return vec4(spotFactor * attenuation( distance(position, positionL) ) * (diffuse + specular), 1.0);
}

void main() {
	if(modeLight == 0){
		FragColor = ambient();
	}
		
	if(modeLight == 1){
		FragColor = puntual();
	}

	if(modeLight == 2){
		FragColor = spot();
	}
}