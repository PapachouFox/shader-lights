varying vec3 v_fragNormal;
varying mat3 v_fragNormalMatrix;
varying float v_lightDistance;
varying vec3 v_surfaceToLight;
varying vec3 v_surfaceToCamera;

uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

void main()
{
    v_fragNormal = gl_Normal;
    v_fragNormalMatrix = gl_NormalMatrix;

    vec4 surfacePos = gl_ModelViewProjectionMatrix * gl_Vertex;
    v_surfaceToLight = normalize(u_LightPosition - surfacePos.xyz);
    v_surfaceToCamera = normalize(u_CameraPosition - surfacePos.xyz);    
    
    v_lightDistance = length(u_LightPosition - surfacePos.xyz);

    //gl_Position = ftransform();
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}