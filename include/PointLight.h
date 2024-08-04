#pragma once

#include <glm/glm.hpp>
#include "Shader.h"

struct PointLight
{
	glm::vec3 m_Position;
	glm::vec3 m_Color;

	void Render(Shader& shader)
	{
		shader.SetUniform3f("u_LightPosition", m_Position);
		shader.SetUniform3f("u_LightColor", m_Color);
	}
};