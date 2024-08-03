#include "Model.h"

Model::Model(const std::string& path)
{
	m_Mesh = new Mesh(path);
}

Model::Model(const Model& other)
{
	m_Mesh = other.m_Mesh;
}

void Model::Render(Shader& shader)
{
	for (auto& diffuse : m_Mesh->m_DiffuseTextures)
	{
		diffuse->Bind();
	}

	m_Mesh->Render(shader);

	for (auto& diffuse : m_Mesh->m_DiffuseTextures)
	{
		diffuse->Unbind();
	}
}