uniform vec3 u_LightPosition;
uniform vec4 u_DiffuseLightColor;

varying vec2 v_TexCoord;

void main() {
	vec3 normal, lightDir;
	vec4 diffuse;
	float NdotL;

	normal = normalize(gl_NormalMatrix * gl_Normal);
	lightDir = normalize(vec3(u_LightPosition));
	
	NdotL = max(dot(normal, lightDir), 0.0);

	diffuse = gl_FrontMaterial.diffuse * u_DiffuseLightColor;
	gl_FrontColor =  NdotL * u_DiffuseLightColor;

	gl_Position = ftransform();
	v_TexCoord = gl_MultiTexCoord0.xy;
}
