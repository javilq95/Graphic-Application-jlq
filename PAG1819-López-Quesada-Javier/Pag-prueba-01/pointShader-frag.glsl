#version 400
in vec4 destinationColor;
out vec4 fColor;
void main(){
	vec2 coord = gl_PointCoord - vec2(0.5);
	if( length (coord) > 0.5){ 
		discard;
	}
	fColor = destinationColor;
}