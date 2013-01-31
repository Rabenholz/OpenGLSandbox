uniform float timer;
attribute vec3 position;
attribute vec4 vexColor;
varying vec4 color;

mat4 view_frustum(float angle_of_view, float aspect_ratio, float z_near, float z_far);
mat4 scale(float x, float y, float z);
mat4 translate(float x, float y, float z);
mat4 rotate_x(float theta);

void main(void)
{
	gl_Position = view_frustum(radians(45.0), 4.0/3.0, 0.0, 10.0) *
					translate(0.0,0.0,4) *
					rotate_x(timer) *
					vec4(position,1.0);
	color = vexColor;
}

mat4 view_frustum(float angle_of_view, float aspect_ratio, float z_near, float z_far) 
{
    return mat4(
        vec4(1.0/tan(angle_of_view),           0.0, 0.0, 0.0),
        vec4(0.0, aspect_ratio/tan(angle_of_view),  0.0, 0.0),
        vec4(0.0, 0.0,    (z_far+z_near)/(z_far-z_near), 1.0),
        vec4(0.0, 0.0, -2.0*z_far*z_near/(z_far-z_near), 0.0)
    );
}

mat4 scale(float x, float y, float z)
{
    return mat4(
        vec4(x,   0.0, 0.0, 0.0),
        vec4(0.0, y,   0.0, 0.0),
        vec4(0.0, 0.0, z,   0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );
}

mat4 translate(float x, float y, float z)
{
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(x,   y,   z,   1.0)
    );
}

mat4 rotate_x(float theta)
{
    return mat4(
        vec4(1.0,         0.0,         0.0, 0.0),
        vec4(0.0,  cos(timer),  sin(timer), 0.0),
        vec4(0.0, -sin(timer),  cos(timer), 0.0),
        vec4(0.0,         0.0,         0.0, 1.0)
    );
}