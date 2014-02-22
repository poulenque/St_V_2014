
Uniform float noise;

float rand(in vec2 c) {
    return fract(sin(dot(c.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

varying vec4 vertex_color;
void main(void){
	vertex_color = gl_Color;
	gl_Position = ftransform()+vec4();
}
