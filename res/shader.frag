#version 440 core

uniform sampler2D u_DiffuseTexture;
uniform vec3 u_Ambient;

in vec2 o_TextureCoords;
in vec3 o_Normals;

void main() {
	vec3 _light = u_Ambient;
	gl_FragColor = texture(u_DiffuseTexture, o_TextureCoords) * vec4(_light, 1.0);
}