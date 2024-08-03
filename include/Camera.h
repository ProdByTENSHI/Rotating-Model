#pragma once

#include "Shader.h"
#include "Transform.h"

class Camera
{
public:
	Camera();

	void Update(Shader& shader);

	// Calculate the Cameras Direction
	const glm::vec3& GetDirection();

	// Returns the Right Axis by doing a Cross Product with the Target Vector and the Up Vector
	const glm::vec3& GetRightAxis();

	// Returns the Up Axis by doing a Cross Product with the Right Axis Vector and the Target Vector
	const glm::vec3& GetUpAxis();

	// Doesnt need to be done every Frame as it doesnt change often
	void CalculateProjectionMatrix(uint32_t width, uint32_t height);

private:
	// Holds the Position and Rotation(The Scale is unused)
	Transform m_Transform;

	glm::mat4 m_ProjectionMatrix;

private:
	const glm::vec3 m_Target = glm::vec3(0.0f, 0.0f, 0.0f);

	const float FOV = 60.0f;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 100.0f;
};