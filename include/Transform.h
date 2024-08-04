#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform
{
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		m_Position = position;
		m_Rotation = rotation;
		m_Scale = scale;

		Scale(m_Scale);
		Rotate(glm::vec3(1.0f, 0.0f, 0.0f), m_Rotation.x);
		Rotate(glm::vec3(0.0f, 1.0f, 0.0f), m_Rotation.y);
		Rotate(glm::vec3(0.0f, 0.0f, 1.0f), m_Rotation.z);
		Translate(m_Position);
	}

	void Translate(const glm::vec3& translation)
	{
		m_Position += translation;
		m_TransformationMatrix = glm::translate(m_TransformationMatrix, translation);
	}

	void Rotate(const glm::vec3& axis, float angle)
	{
		m_Rotation += axis * angle;
		m_TransformationMatrix = glm::rotate(m_TransformationMatrix, angle, axis);
	}

	void Scale(const glm::vec3& scale)
	{
		m_Scale += scale;
		m_TransformationMatrix = glm::scale(m_TransformationMatrix, scale);
	}

	glm::mat4 m_TransformationMatrix = glm::mat4(1.0f);
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};