#pragma once

#include <map>
#include <vector>

#include "Mesh.h"

class Model
{
public:
	Model(const std::string& path);
	Model(const Model& other);

	void Render(Shader& shader);

private:
	Mesh* m_Mesh;
};