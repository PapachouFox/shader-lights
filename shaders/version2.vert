varying vec3 v_FragVert;
varying vec2 v_FragTexCoord;
varying vec3 v_FragNormal;

uniform sampler2D u_Texture;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;
uniform vec4 u_DiffuseLightColor;

void main() {
    // Pass some variables to the fragment shader
    v_FragTexCoord = gl_MultiTexCoord0.xy;
    v_FragNormal = gl_Normal;
    v_FragVert = gl_Vertex.xyz;
    
    // Apply all matrix transformations to vert
    gl_Position = gl_ModelViewMatrix * vec4(gl_Vertex);
}