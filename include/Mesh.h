#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

#include "Transform.h"
#include "Shader.h"
#include "Texture.h"

struct Vertex
{
	GLfloat m_Position[3];
	GLfloat m_Normals[3];
	GLfloat m_TextureCoords[2];
};

struct Material
{
	glm::vec3 m_Ambient;
	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;
};

class Mesh
{
public:
	Mesh(const std::string& path);
	Mesh(const Mesh& other);

	void Render(Shader& shader);

	const aiScene* m_Scene = nullptr;
	Transform m_Transform
		= { glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.3f) };

	std::vector<std::shared_ptr<Texture>> m_DiffuseTextures;

	glm::vec3 m_Color = glm::vec3(1.0f);

private:
	std::vector<aiMesh*> m_Meshes;
	std::vector<Vertex> m_Vertices;
	std::vector<GLuint> m_Indices;

	Material m_Material = { glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f) };

private:
	void ProcessNode(const aiNode* node);
	void ProcessMesh(aiMesh* mesh);

	const std::vector<std::shared_ptr<Texture>>& LoadMaterialTextures(aiMaterial& material,
		aiTextureType type);

};