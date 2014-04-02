varying vec2 v_TexCoord;
varying vec4 v_specular;
varying vec4 v_ambient;
varying vec4 v_diffuse;

uniform sampler2D u_texture;
uniform sampler2D u_normal;

void main()
{
    vec4 color = texture2D(u_texture, vec2(v_TexCoord));
    vec4 ncolor = texture2D(u_normal, vec2(v_TexCoord));
    color = v_specular + color*v_ambient + color*v_diffuse;
    gl_FragColor = color;
}
