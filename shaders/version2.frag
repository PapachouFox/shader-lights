varying vec3 v_FragVert;
varying vec2 v_FragTexCoord;
varying vec3 v_FragNormal;

uniform sampler2D u_Texture;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;
uniform vec4 u_DiffuseLightColor;

void main() {
    //calculate normal in world coordinates
    //mat3 normalMatrix = gl_NormalMatrix;
    vec3 normal = normalize(gl_NormalMatrix * v_FragNormal);
    
    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = u_LightPosition - v_FragVert;

    //calculate the cosine of the angle of incidence (brightness)
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(u_Texture, v_FragTexCoord)
    gl_FragColor = brightness * u_DiffuseLightColor * texture2D(u_Texture, v_FragTexCoord);
}