varying vec3 v_fragNormal;
varying mat3 v_fragNormalMatrix;
varying float v_lightDistance;
varying vec3 v_surfaceToLight;
varying vec3 v_surfaceToCamera;

uniform sampler2D u_texture;
uniform sampler2D u_normal;
uniform sampler2D u_specular;
uniform sampler2D u_night;

uniform vec4 u_DiffuseLightColor;
uniform vec4 u_SpecularLightColor;
uniform vec4 u_AmbientLightColor;
uniform float u_ModelShininess;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

void main()
{
    vec3 specular, diffuse, ambient, normal;
    
    vec3 color = texture2D(u_texture, gl_TexCoord[0].st).rgb;
    vec3 ncolor = texture2D(u_normal, gl_TexCoord[0].st).rgb;
    vec3 scolor = texture2D(u_specular, gl_TexCoord[0].st).rgb;
    vec3 offcolor = texture2D(u_night, gl_TexCoord[0].st).rgb;

    normal = normalize(v_fragNormalMatrix * v_fragNormal);
    normal = normalize((ncolor * 2.0) - 1.0);
    float diffuseCoeff = max(0.0, dot(normal, v_surfaceToLight));
    
    if(diffuseCoeff > 0.0 && u_ModelShininess > 0.0){
        vec3 reflectionVector = reflect(-v_surfaceToLight, normal);
        float cosAngle = max(0.0, dot(v_surfaceToCamera, reflectionVector));
        specular = pow(cosAngle, u_ModelShininess) * u_SpecularLightColor.xyz;
    }

    diffuse = diffuseCoeff * u_DiffuseLightColor.xyz;
    ambient = u_AmbientLightColor.xyz;

    float attenuation = 1.0 / (1.0 + 0.00002 * pow(v_lightDistance, 2.0));
    color = color * ambient + (diffuse * color + specular * (scolor + 0.1));
    if(diffuse.x == 0.0){
        color = offcolor * ambient;
    }

    gl_FragColor = vec4(color, 1.0);
}
