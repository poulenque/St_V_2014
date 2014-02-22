uniform sampler2D color;
varying vec2 vTexCoord;

const float blurSize = 1.0/512.0;


void main(void){
	gl_FragColor=texture2D(color, vTexCoord.xy);
	// gl_FragColor=vec4(1,1,1,1);
	// gl_FragColor=texture2D(color, vec2(vTexCoord.x - 4.0*blurSize, vTexCoord.y)) * 0.05;
}
