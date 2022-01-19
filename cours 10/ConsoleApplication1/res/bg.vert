void main()
{
	// transforme la position du vertex
	vec4 worldPos = gl_Vertex;
	worldPos.x += 100;
	gl_Position = gl_ModelViewProjectionMatrix * worldPos;
	
    // transforme les coordonnees de texture
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // transmet la couleur
    gl_FrontColor = gl_Color;
	
}