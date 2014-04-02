varying vec2 vTexCoord;
uniform sampler2D u_texture;
//uniform sampler2D u_normal;
void main()
{
        vec4 color = texture2D(u_texture, vec2(vTexCoord));
        //vec4 normal = texture2D(u_normal, vec2(vTexCoord));
        gl_FragColor = gl_Color*color;
}
