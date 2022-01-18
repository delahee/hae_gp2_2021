//#define HAS_TEXTURE
//#define HAS_UNIFORM_COLOR

#ifdef HAS_TEXTURE
uniform sampler2D texture;
#endif

#ifdef HAS_UNIFORM_COLOR
uniform vec4 col;
#endif

void main()
{
    // récupère le pixel dans la texture
	#ifdef HAS_TEXTURE
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	#else
	vec4 pixel = vec4(1.0,1.0,1.0,1.0);
	#endif
	
	#ifdef HAS_UNIFORM_COLOR
	pixel *= col;
	#endif

    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;
	//gl_FragColor = vec4(1,0,1,1);
}