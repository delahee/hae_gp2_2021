uniform float time;
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // transmet la couleur
    gl_FrontColor = gl_Color;
	
}