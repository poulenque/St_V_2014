
varying vec2 vTexCoord;

void main(void){
	gl_Position = vec4(gl_Vertex.xy, 0.0, 1.0);
	vTexCoord = gl_Vertex.xy * 0.5 + 0.5;
}