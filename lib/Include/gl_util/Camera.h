#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	glm::vec3 m_Pos;
	glm::vec3 m_Front;
	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
		: m_Pos(pos), m_Front(front), m_Up(up) {};
	~Camera() {};

	glm::mat4 createView()
	{
		return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
	}
	float getFOV()
	{
		return glm::radians(fov);
	}
	void processCameraInput(GLFWwindow* window, float deltaTime)
	{
		const float cameraSpeed = 15.0f * deltaTime;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			m_Pos += cameraSpeed * m_Front;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_Pos -= glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_Pos -= cameraSpeed * m_Front;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;
	}
	void onMouseCallback(float offsetX, float offsetY)
	{
		static float yaw = -glm::half_pi<float>();
		static float pitch = 0;

		yaw += offsetX;
		pitch += offsetY;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(yaw) * cos(pitch);
		direction.y = sin(pitch);
		direction.z = sin(yaw) * cos(pitch);

		m_Front = glm::normalize(direction);
	}
	void onScrollCallback(float offsetX, float offsetY)
	{
		fov -= (float)offsetY;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 180.0f)
			fov = 180.0f;
	}
	glm::vec3 getPos() const
	{
		return m_Pos;
	}
	glm::vec3 getDir() const
	{
		return m_Front;
	}
private:
	glm::vec3 m_Up;
	float fov = 45.0f;
};
