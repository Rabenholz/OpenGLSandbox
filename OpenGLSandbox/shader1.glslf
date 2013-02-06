varying vec4 color;
void main(void)
{
	//if((mod(floor(gl_FragCoord.x),20) < 10 && mod(floor(gl_FragCoord.y),20) < 10) ||
	//		(mod(floor(gl_FragCoord.x),20) >= 10 && mod(floor(gl_FragCoord.y),20) >= 10))
	vec2 localPos = vec2(mod(floor(gl_FragCoord.x),20), mod(floor(gl_FragCoord.y),20));
	if((localPos.x < 10 && localPos.y < 10 && !(pow(localPos.x-5,2) + pow(localPos.y-5,2) < 16)) ||
		(localPos.x >= 10 && localPos.y >= 10 && !(pow(localPos.x-5,2) + pow(localPos.y-5,2) < 16)))
		gl_FragColor = vec4(1.0-color.x,1.0-color.y,1.0-color.z,1.0);
	else
		gl_FragColor = color;
}