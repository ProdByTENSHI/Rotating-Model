#version 440 core

uniform sampler2D u_DiffuseTexture;
uniform vec3 u_Ambient;
uniform vec3 u_Diffuse;
uniform vec3 u_Specular;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;

in vec3 o_FragPos;
in vec2 o_TextureCoords;
in vec3 o_Normals;

void main() {
	vec3 _lightDirection = normalize(u_LightPosition - o_FragPos);
	vec3 _diffuse = max(dot(normalize(o_Normals), _lightDirection), 0.0) * u_LightColor * u_Diffuse;

	vec3 _finalLight = (u_Ambient + _diffuse);
	gl_FragColor = texture(u_DiffuseTexture, o_TextureCoords) * vec4(_finalLight, 1.0);
}