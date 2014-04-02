varying vec2 v_TexCoord;

uniform vec3 u_LightPosition;
uniform vec4 u_AmbientLightColor;
uniform vec4 u_DiffuseLightColor;
uniform vec4 u_SpecularLightColor;

void main()
{
	vec3 normal, lightDir, viewVector, halfVector;
	vec4 specular = vec4(0.0);
	float NdotL,NdotHV;

	normal = normalize(gl_NormalMatrix * gl_Normal);
	lightDir = normalize(vec3(u_LightPosition));

	NdotL = max(dot(normal, lightDir), 0.0);

	if (NdotL > 0.0) {
		NdotHV = max(dot(normal, normalize(u_LightPosition)),0.0);
		specular = u_SpecularLightColor * pow(NdotHV, gl_FrontMaterial.shininess);
	}

	gl_FrontColor = normalize(u_AmbientLightColor + NdotL * u_DiffuseLightColor + specular);
	gl_Position = ftransform();
	v_TexCoord = gl_MultiTexCoord0.xy;	
} 
