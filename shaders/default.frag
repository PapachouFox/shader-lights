varying vec2 v_TexCoord;
uniform sampler2D u_texture;

void main()
{
	vec4 color = texture2D(u_texture, vec2(v_TexCoord));
	gl_FragColor = color*gl_Color;
}
