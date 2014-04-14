varying vec4 v_specular;
varying vec4 v_ambient;
varying vec4 v_diffuse;
varying float v_lightDistance;

uniform sampler2D u_texture;
uniform sampler2D u_normal;
uniform sampler2D u_specular;
uniform sampler2D u_night;

void main()
{
    vec4 color = texture2D(u_texture, gl_TexCoord[0].st);
    vec4 ncolor = texture2D(u_normal, gl_TexCoord[0].st);
    vec4 scolor = texture2D(u_specular, gl_TexCoord[0].st);
    vec4 offcolor = texture2D(u_night, gl_TexCoord[0].st);

    float attenuation = 1.0 / (1.0 + 0.00002 * pow(v_lightDistance, 2.0));
    color = color * v_ambient + attenuation*(v_diffuse * color + v_specular * (scolor + 0.1));
    if(v_diffuse.x == 0.0){
        color = offcolor;
    }
    gl_FragColor = color;
}
