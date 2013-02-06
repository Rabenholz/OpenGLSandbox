uniform float timer;
uniform mat4 perspectiveMatrix;
uniform vec3 offset;

attribute vec3 position;
attribute vec4 vexColor;

varying vec4 color;

void main(void)
{
	vec4 cameraPos = position + vec4(offset, 0.0);
	gl_Position = perspectiveMatrix * cameraPos;
	color = vexColor;
}