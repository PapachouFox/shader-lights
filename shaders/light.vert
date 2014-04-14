varying vec4 v_specular;
varying vec4 v_ambient;
varying vec4 v_diffuse;
varying float v_lightDistance;

uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

uniform vec4 u_DiffuseLightColor;
uniform vec4 u_SpecularLightColor;
uniform vec4 u_AmbientLightColor;
uniform float u_ModelShininess;

void main()
{
    vec3 normal = gl_NormalMatrix * gl_Normal;
    vec4 surfacePos = gl_ModelViewMatrix * gl_Vertex;
    vec3 surfaceToLight = normalize(u_LightPosition - surfacePos.xyz);
    float diffuseCoeff = max(0.0, dot(normal, surfaceToLight));

    if(diffuseCoeff > 0.0){
        vec3 incidenceVector = -surfaceToLight; //a unit vector
        vec3 reflectionVector = reflect(incidenceVector, normal); //also a unit vector
        vec3 surfaceToCamera = normalize(u_CameraPosition - surfacePos.xyz); //also a unit vector
        float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));

        if(u_ModelShininess > 0.0){
            v_specular = pow(cosAngle, u_ModelShininess) * u_SpecularLightColor;
        }
    }

    v_diffuse = diffuseCoeff * u_DiffuseLightColor;
    v_ambient = u_AmbientLightColor;

    v_lightDistance = length(u_LightPosition - surfacePos.xyz);

    gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
}