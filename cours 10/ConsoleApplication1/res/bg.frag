uniform sampler2D 	texture;
uniform vec4 		col;
uniform vec4 		colAdd;
uniform vec4 		colMul;
uniform mat4 		colTrans;
uniform float 		time;

vec4 blur9(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.3846153846) * direction;
  vec2 off2 = vec2(3.2307692308) * direction;
  color += texture2D(image, uv) * 0.2270270270;
  color += texture2D(image, uv + (off1 / resolution)) * 0.3162162162;
  color += texture2D(image, uv - (off1 / resolution)) * 0.3162162162;
  color += texture2D(image, uv + (off2 / resolution)) * 0.0702702703;
  color += texture2D(image, uv - (off2 / resolution)) * 0.0702702703;
  return color;
}

void main()
{
    // recup le pixel dans la texture
	//vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec2 resolution = vec2(1024,1024);
	
	float xscale = 2.0;
	float yscale = 2.0;
	
	vec4 pixel = blur9( texture,gl_TexCoord[0].xy, resolution, vec2(xscale,0));
	
	pixel =  0.5 * (pixel ) + 0.5 * blur9( texture,gl_TexCoord[0].xy, resolution, vec2(0,yscale));
	
    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;
	//gl_FragColor = vec4(1,0,1,1);
}