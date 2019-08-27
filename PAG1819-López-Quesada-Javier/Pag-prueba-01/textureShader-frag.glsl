#version 400
#define M_PI 3.1415926535897932384626433832795

in vec3 position;
in vec3 normal;
in vec2 texCoord;

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

uniform sampler2D TexSamplerColor;
uniform sampler2D TexSamplerShininess;

layout (location = 0) out vec4 FragColor;

vec4 ambient() {
	vec4 texColor = texture(TexSamplerColor, texCoord);
	vec4 texShininess = texture(TexSamplerShininess, texCoord);
	vec3 Kad = texColor.rgb;
	vec3 Kas = texShininess.rgb;
	return vec4(Ia * Kad * Kas, 1.0);
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

	vec4 texColor = texture(TexSamplerColor, texCoord);
	vec3 Kad = texColor.rgb;
	vec3 diffuse = (Id * Kad * max( dot(l,n), 0.0));

	vec3 specular;

	vec4 texShininess = texture(TexSamplerShininess, texCoord);
	vec3 Kas = texShininess.rgb;

	if (dot(l, n) < 0.0) {
		specular = vec3(0.0);
	} else {
		specular = (Is * Kas * pow( max( dot(r,v), 0.0), 1 + (texShininess.a * shininess) ));
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

	vec4 texColor = texture(TexSamplerColor, texCoord);
	vec3 Kad = texColor.rgb;
	vec3 diffuse = (Id * Kad * max( dot(l,n), 0.0));

	vec3 specular;

	vec4 texShininess = texture(TexSamplerShininess, texCoord);
	vec3 Kas = texShininess.rgb;

	if (dot(l, n) < 0.0) {
		specular = vec3(0.0);
	} else {
		specular = (Is * Kas * pow( max( dot(r,v), 0.0), 1 + (texShininess.a * shininess)) );
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