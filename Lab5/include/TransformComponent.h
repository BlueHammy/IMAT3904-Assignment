#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#define NO_ROLL (1)

class TransformComponent : public Component
{

	const float moveStepsize = 1.0f / 256.0f;
	const float rotateStepsize = 1.0f / 512.0f;

public:
	glm::vec3 m_position;
	glm::vec3 m_scale;

private:
#if NO_ROLL

	glm::quat m_orientationYaw;
	glm::quat m_orientationPitch;

#else

	glm::quat m_orientation;

#endif

public:


	glm::quat getOrientation()
	{
#if NO_ROLL
		return m_orientationYaw * m_orientationPitch;
#else
		return m_orientation;
#endif
	}


	void OnUpdate(float dt) override {}
	void OnMessage(const std::string m) override
	{
		if (m == "rotateLeft")
		{
			yaw(rotateStepsize);
		}
		if (m == "rotateRight")
		{
			yaw(-rotateStepsize);
		}

		if (m == "rotateUp")
		{
			pitch(-rotateStepsize);	
		}
		if (m == "rotateDown")
		{
			pitch(rotateStepsize);
		}
		if (m == "moveForward")
		{
			glm::vec3 v = glm::vec3(0, 0, -moveStepsize);
#if NO_ROLL
			translate(getOrientation() * v);
#else
			translate(m_orientation * v);
#endif
		}
		if (m == "moveBackward")
		{
			glm::vec3 v = glm::vec3(0, 0, moveStepsize);
#if NO_ROLL
			translate(getOrientation() * v);
#else
			translate(m_orientation * v);
#endif
		}

		if (m == "moveUp")
		{
			glm::vec3 v = glm::vec3(0, moveStepsize, 0);
#if NO_ROLL
			translate(getOrientation() * v);
#else
			translate(m_orientation * v);
#endif
		}
		if (m == "moveDown")
		{
			glm::vec3 v = glm::vec3(0, -moveStepsize, 0);
#if NO_ROLL
			translate(getOrientation() * v);
#else
			translate(m_orientation * v);
#endif
		}
		if (m == "reset")
		{
			m_position = glm::vec3(0, 0, 0);
#if NO_ROLL
			m_orientationYaw = glm::quat(1, 0, 0, 0);
			m_orientationPitch = glm::quat(1, 0, 0, 0);
#else
			m_orientation = glm::quat(1, 0, 0, 0);
#endif
		}

	}

#if NO_ROLL
	TransformComponent() : m_position(0), m_orientationYaw(1, 0, 0, 0), m_orientationPitch(1, 0, 0, 0), m_scale(1.0f) {}
	TransformComponent(const glm::vec3& pos) : m_position(pos), m_orientationYaw(1, 0, 0, 0), m_orientationPitch(1, 0, 0, 0), m_scale(1.0f) {}

	TransformComponent(const glm::vec3& pos, const glm::quat& orientY) : m_position(pos), m_orientationYaw(orientY), m_orientationPitch(1, 0, 0, 0), m_scale(1.0f) {}
	TransformComponent(const glm::vec3& pos, const glm::quat& orientY, const glm::quat& orientP) : m_position(pos), m_orientationYaw(orientY), m_orientationPitch(orientP), m_scale(1.0f) {}
#else
	TransformComponent() : m_position(0), m_orientation(1, 0, 0, 0), m_scale(1.0f) {}
	TransformComponent(const glm::vec3& pos) : m_position(pos), m_orientation(1, 0, 0, 0), m_scale(1.0f) {}
	TransformComponent(const glm::vec3& pos, const glm::quat& orient) : m_position(pos), m_orientation(orient), m_scale(1.0f) {}
	TransformComponent(const glm::vec3& pos, const glm::quat& orient, const glm::vec3& scale) : m_position(pos), m_orientation(orient), m_scale(scale) {}
#endif
	const glm::vec3& position() const { return m_position; }
#if NO_ROLL
#else
	const glm::quat& orientation() const { return m_orientation; }
#endif
	const glm::vec3& scale() const { return m_scale; }

	glm::mat4 getModelMatrix()
	{
		glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), m_position);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
#if NO_ROLL
		glm::mat4 rotMatrix = glm::mat4_cast(getOrientation());
#else
		glm::mat4 rotMatrix = glm::mat4_cast(m_orientation);
#endif
		return transMatrix * rotMatrix * scaleMatrix;
	}

	void translate(const glm::vec3 &v) { m_position += v; }
	void translate(float x, float y, float z) { m_position += glm::vec3(x, y, z); }


#if NO_ROLL
#else
	void rotate(float angle, float x, float y, float z) {

#if 1
		glm::vec3 anglesBefore = glm::eulerAngles(m_orientation); 

		m_orientation *= glm::angleAxis(angle, glm::vec3(x, y, z)); 

		glm::vec3 anglesAfter = glm::eulerAngles(m_orientation); 

#else

		m_orientation *= glm::angleAxis(angle, glm::vec3(x, y, z) * m_orientation); 
#endif
	}
#endif
	void scaleUp(const glm::vec3 &v) { m_scale += v; }
	void scaleUp(float x, float y, float z) { m_scale += glm::vec3(x, y, z); }

#if NO_ROLL
	void yaw(float angle)
	{
		m_orientationYaw *= glm::angleAxis(angle, glm::vec3(0, 1, 0));
	}
	void pitch(float angle)
	{
		m_orientationPitch *= glm::angleAxis(angle, glm::vec3(1, 0, 0));
	}
#else
	void yaw(float angle) { rotate(angle, 0.0f, 1.0f, 0.0f); }
	void pitch(float angle) { rotate(angle, 1.0f, 0.0f, 0.0f); }
	void roll(float angle) { rotate(angle, 0.0f, 0.0f, 1.0f); }
#endif

	glm::vec3 getEulerAngles()
	{
#if NO_ROLL
		glm::quat m_orientation = m_orientationYaw * m_orientationPitch;
#endif
		return glm::eulerAngles(m_orientation); 
	}
};
