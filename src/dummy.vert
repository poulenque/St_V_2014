varying vec4 vertex_color;
void main(void){
	vertex_color = gl_Color;
	gl_Position = ftransform();
}