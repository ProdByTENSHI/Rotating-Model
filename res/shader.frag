#version 440 core

uniform sampler2D u_DiffuseTexture;

uniform vec3 u_Color;
uniform vec3 u_Ambient;
uniform vec3 u_Diffuse;
uniform float u_SpecularStrength;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

in vec3 o_FragPos;
in vec2 o_TextureCoords; 
in vec3 o_Normals;

const float SPECULAR_SHININESS = 128;

void main() {
	// Diffuse Lighting	
	//	- 1. Calculate Light Direction by Subtracting the Position of the Light with the Frag Position
	//	- 2. Calculate Diffuse Factor by calculating the Dot Product of the normalized Normals and the Light Direction
	//	- 3. Make sure the Diffuse Factor stays between 0 and 1 by wrapping it around a max()
	vec3 _lightDirection = normalize(u_LightPosition - o_FragPos);
	vec3 _normalizedNormals = normalize(o_Normals);
	vec3 _diffuse = max(dot(_normalizedNormals, _lightDirection), 0.0) * u_LightColor * u_Diffuse;

	// Specular Lighting
	//	- 1. Calculate the View Direction by Subtracting the View Position by the Frag Position
	//	- 2. Calculate the Reflection Direction of the Light by inversing the Light Direction to get the Direction FROM the Light Source
	//			and and calling the reflect function with the Normals as the second Param
	//	- 3. Calculate the Specular Factor by calculating the Dot Product between the View Dir and the Reflect Dir and raise it to the Power of the Shininess Value(Hardcoded at 32 rn)
	//  - 4. Calculate the final Specular Light by multiplying it with the Specular Strength and the Light Color
	vec3 _viewDir = normalize(u_CameraPosition - o_FragPos);
	vec3 _reflectDir = reflect(-_lightDirection, _normalizedNormals);
	float _specular = pow(max(dot(_viewDir, _reflectDir), 0.0), SPECULAR_SHININESS);
	vec3 _specularLight = (_specular * u_LightColor) * u_SpecularStrength;

	vec3 _finalLight = (u_Ambient + _diffuse + _specular) * u_Color;
	gl_FragColor = texture(u_DiffuseTexture, o_TextureCoords) * vec4(_finalLight, 1.0);
}