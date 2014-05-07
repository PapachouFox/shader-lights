varying vec3 v_fragNormal;
varying mat3 v_fragNormalMatrix;
varying float v_lightDistance;
varying vec3 v_surfaceToLight;
varying vec3 v_surfaceToCamera;

uniform sampler2D u_texture;

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
 
    normal = v_fragNormal;
    //apply normal map
    //vec3 bump = normalize((ncolor * 2.0) - 1.0);

    float diffuseCoeff = max(0.0, dot(normal, v_surfaceToLight));

    //quadratic attenuation
    float quadratic = 0.00002;
    float attenuation = 1.0 / (quadratic * pow(v_lightDistance, 2.0));

    if(diffuseCoeff > 0.0 && u_ModelShininess > 0.0){
        vec3 reflectionVector = reflect(-v_surfaceToLight, normal);

        float cosAngle = max(0.0, dot(v_surfaceToCamera, reflectionVector));

        specular = pow(cosAngle, u_ModelShininess*0.5) * u_SpecularLightColor.xyz;
    }

    diffuse = diffuseCoeff * u_DiffuseLightColor.xyz;
    ambient = u_AmbientLightColor.xyz;

    if(diffuse.x == 0.0){
        color =  color * ambient;
    }else{
        //apply attenuation
        diffuse = diffuse * attenuation;
        specular = specular * attenuation;
        color = color * ambient + (diffuse * color + specular);
    }

    gl_FragColor = vec4(color, 0.6);
}