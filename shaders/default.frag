varying vec2 v_TexCoord;
uniform sampler2D u_texture;
uniform sampler2D u_normal;

void main()
{
    vec4 color = texture2D(u_texture, vec2(v_TexCoord));
    vec4 ncolor = texture2D(u_normal, vec2(v_TexCoord));
    gl_FragColor = (color+ncolor)*gl_Color;
}
