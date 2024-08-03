#include "Camera.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Globals.h"

const float MOVEMENT_SPEED = 1.0f;

Camera::Camera() : m_ProjectionMatrix(glm::mat4(1.0f)), m_Transform(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f), glm::vec3(3.0f))
{
	m_Transform.m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
	m_Transform.m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	CalculateProjectionMatrix(g_WindowWidth, g_WindowHeight);

	chroma::EventHandler<int> _onKeyDown([this](int key)
		{
			switch (key)
			{
			case GLFW_KEY_W:
				m_Transform.Translate(glm::vec3(0.0f, 0.0f, -MOVEMENT_SPEED));
				break;

			case GLFW_KEY_S:
				m_Transform.Translate(glm::vec3(0.0f, 0.0f, MOVEMENT_SPEED));
				break;

			case GLFW_KEY_SPACE:
				m_Transform.Rotate(glm::vec3(0.0f, 1.0f, 0.0f), -MOVEMENT_SPEED);
				break;

			case GLFW_KEY_LEFT_SHIFT:
				m_Transform.Rotate(glm::vec3(0.0f, 1.0f, 0.0f), MOVEMENT_SPEED);
			}
		});
	g_OnKeyDown.Subscribe(_onKeyDown);
}

void Camera::Update(Shader& shader)
{
	glm::mat4 _view = glm::mat4(1.0f);
	_view = glm::lookAt(m_Transform.m_Position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	shader.SetUniformMat4("u_Projection", m_ProjectionMatrix);
	shader.SetUniformMat4("u_View", _view);
}

const glm::vec3& Camera::GetDirection()
{
	return glm::normalize(m_Transform.m_Position - m_Target);
}

const glm::vec3& Camera::GetRightAxis()
{
	return glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), GetDirection()));
}

const glm::vec3& Camera::GetUpAxis()
{
	return glm::normalize(glm::cross(GetDirection(), GetRightAxis()));
}

void Camera::CalculateProjectionMatrix(uint32_t width, uint32_t height)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(FOV), (float)width / (float)height, NEAR_PLANE, FAR_PLANE);
}