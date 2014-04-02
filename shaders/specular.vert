varying vec2 vTexCoord;
void main()
{
	vec3 normal, lightDir, viewVector, halfVector;
	vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
	float NdotL,NdotHV;

	lightDir = normalize(vec3(gl_LightSource[0].position));

	NdotL = max(dot(normal, lightDir), 0.0);

	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;

	if (NdotL > 0.0) {
		NdotHV = max(dot(normal, normalize(gl_LightSource[0].halfVector.xyz)),0.0);
		specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
	}

	gl_FrontColor = globalAmbient + NdotL * diffuse + ambient + specular;
	gl_Position = ftransform();
	vTexCoord = gl_MultiTexCoord0.xy;	
} 
