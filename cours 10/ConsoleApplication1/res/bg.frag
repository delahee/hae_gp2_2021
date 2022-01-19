uniform sampler2D 	texture;
uniform vec4 		col;
uniform vec4 		colAdd;
uniform vec4 		colMul;
uniform mat4 		colTrans;
uniform float time;
void main()
{
    // recup le pixel dans la texture
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	
	//on connait les UV 
	// essayer de faire appliquer la coloration a une ligne sur 2 ou sur une plage
	
	if( ( mod(gl_TexCoord[0].y , 0.2)) > 0.1 ){
		vec2 uvFinal = gl_TexCoord[0].xy;
		uvFinal.x += 0.2 * (mod(time*0.3,0.2));
		pixel = texture2D(texture, uvFinal);
		pixel.g = 0.0;
	}
	//pixel = vec4( gl_TexCoord[0].x,gl_TexCoord[0].y,0,1); 
	
	pixel *= col;
	
	pixel += colAdd;
	pixel *= colMul;
	pixel = colTrans * pixel;
	
    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;
	//gl_FragColor = vec4(1,0,1,1);
}