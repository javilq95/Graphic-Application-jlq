#version 400
layout (location = 0) out vec4 fColor;
void main() {
	if (gl_FrontFacing) {
		fColor = vec4(0.0, 1.0, 0.0, 1.0);
	} else {
		fColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
}