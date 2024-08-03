#version 440 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textureCoords;

out vec2 o_TextureCoords;
out vec3 o_Normals;

uniform mat4 u_ModelTransform;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
	o_TextureCoords = textureCoords;
	o_Normals = normals;

	gl_Position = u_Projection * u_View * u_ModelTransform * vec4(pos.x, pos.y, pos.z, 1.0);
}