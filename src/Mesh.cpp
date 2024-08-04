#include "Mesh.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Globals.h"
#include "Random.h"
#include "DebugUtil.h"

GLuint vao;
GLuint vbo;
GLuint ebo;

Mesh::Mesh(const std::string& path)
{
	Assimp::Importer _importer;
	m_Scene = _importer.ReadFile(path,
		aiProcess_Triangulate | aiProcess_FlipUVs |
		aiProcess_GenNormals | aiProcess_CalcTangentSpace);

	if (!m_Scene || m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_Scene->mRootNode)
	{
		std::cerr << "Could not load Mesh from Path: " << path << std::endl;
		std::cerr << "Assimp Error: " << _importer.GetErrorString() << std::endl;
		return;
	}

	ProcessNode(m_Scene->mRootNode);

	for (int i = 0; i < m_Meshes.size(); i++)
	{
		ProcessMesh(m_Meshes[i]);
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), &m_Indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, m_Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, m_Normals));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)(offsetof(Vertex, m_TextureCoords)));

	glBindVertexArray(0);

	std::cout << "Loaded Mesh " << path << std::endl;
	std::cout << "Mesh Vertices: " << m_Vertices.size() << std::endl;
	std::cout << "Mesh Indices: " << m_Indices.size() << std::endl;
}

Mesh::Mesh(const Mesh& other)
{
	m_Scene = other.m_Scene;
	m_Transform = other.m_Transform;
	m_Meshes = other.m_Meshes;
	m_Vertices = other.m_Vertices;
	m_Indices = other.m_Indices;

	static int i = 0;
	++i;
	std::cout << i << std::endl;
}

void Mesh::Render(Shader& shader)
{
	glBindVertexArray(vao);

	m_Transform.Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.01f);

	shader.SetUniformMat4("u_ModelTransform", m_Transform.m_TransformationMatrix);
	shader.SetUniform3f("u_Color", m_Color);
	shader.SetUniform3f("u_Ambient", glm::vec3(g_Ambient[0], g_Ambient[1], g_Ambient[2]));
	shader.SetUniform3f("u_Diffuse", glm::vec3(g_Diffuse[0], g_Diffuse[1], g_Diffuse[2]));
	shader.SetUniform1f("u_SpecularStrength", g_SpecularStrength);

	//glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, NULL);
	glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
	glBindVertexArray(0);
}

void Mesh::ProcessNode(const aiNode* node)
{
	// Process Node Meshes
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		m_Meshes.push_back(m_Scene->mMeshes[node->mMeshes[i]]);
	}

	// Recursively Process Child Meshes
	for (int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i]);
	}
}

void Mesh::ProcessMesh(aiMesh* mesh)
{
	static int _meshCount = 0;
	++_meshCount;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex _vertex;
		auto& _position = mesh->mVertices[i];
		auto& _textureCoords = mesh->mTextureCoords[0][i];

		_vertex.m_Position[0] = _position.x;
		_vertex.m_Position[1] = _position.y;
		_vertex.m_Position[2] = _position.z;

		if (mesh->HasNormals())
		{
			_vertex.m_Normals[0] = mesh->mNormals[i].x;
			_vertex.m_Normals[1] = mesh->mNormals[i].y;
			_vertex.m_Normals[2] = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			_vertex.m_TextureCoords[0] = _textureCoords.x;
			_vertex.m_TextureCoords[1] = _textureCoords.y;
		}

		m_Vertices.push_back(_vertex);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		auto& face = mesh->mFaces[i];
		for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
			m_Indices.push_back(face.mIndices[j]);
	}

	aiMaterial* _material = m_Scene->mMaterials[mesh->mMaterialIndex];
	if (!_material)
	{
		std::cerr << "No Material loaded for Mesh " << _meshCount << std::endl;
		return;
	}

	m_DiffuseTextures = LoadMaterialTextures(*_material, aiTextureType_DIFFUSE);
}

const std::vector<std::shared_ptr<Texture>>& Mesh::LoadMaterialTextures(aiMaterial& material, aiTextureType type)
{
	std::vector<std::shared_ptr<Texture>> _textures;

	for (int i = 0; i < material.GetTextureCount(type); i++)
	{
		aiString _path;

		material.GetTexture(type, i, &_path);
		std::shared_ptr<Texture> _texture =
			g_RessourceManager->LoadTexture(_path.C_Str(), type);
		if (_texture)
			_textures.push_back(_texture);
	}

	return _textures;
}