uniform vec4 u_AmbientLightColor;

varying vec2 v_TexCoord;

void main()
{
	gl_FrontColor =  u_AmbientLightColor;
	gl_Position = ftransform();
	v_TexCoord = gl_MultiTexCoord0.xy;
}
