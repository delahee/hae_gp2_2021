uniform sampler2D 	texture;
uniform vec4 		col;
uniform vec4 		colAdd;
uniform vec4 		colMul;
uniform mat4 		colTrans;

void main()
{
    // recup le pixel dans la texture
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	
	pixel *= col;
	
	pixel += colAdd;
	pixel *= colMul;
	pixel = colTrans * pixel;
	
    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;
}