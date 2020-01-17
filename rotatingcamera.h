#pragma once
#ifndef ROTATINGCAMERA_H
#define ROTATINGCAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include "camera.h"

const float DISTANCE = 5.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class RotatingCamera : public Camera
{
public:
	// Angles 
	float AngleZ;
	float AngleX;
	// Distance
	float Distance;

	// Constructor with vectors
	RotatingCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float distance = DISTANCE) : Camera{ position = glm::vec3(0.0f, 0.0f, 0.0f), up = glm::vec3(0.0f, 1.0f, 0.0f), yaw = YAW, pitch = PITCH }
	{
		AngleZ = -Yaw;
		AngleX = Pitch;
		Distance = distance;
	}
	// Constructor with scalar values
	RotatingCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float distance = DISTANCE) : Camera{ posX, posY, posZ, upX, upY, upZ, yaw, pitch } 
	{
		AngleZ = -Yaw;
		AngleX = Pitch;
		Distance = distance;
	}

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		//return glm::lookAt(Position, glm::vec3(0.0f, 0.0f, 0.0f), Up);
	 	return glm::lookAt(Position, Position + Front, Up);

	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		std::cout << "rotating camera" << std::endl;
		float angularVelocity = SPEED * deltaTime * 10;
		if (direction == FORWARD)
		{
			Distance -= SPEED * deltaTime;
		}
		if (direction == BACKWARD)
		{
			Distance += SPEED * deltaTime;
		}
		if (direction == RIGHT)
		{
			AngleZ -= angularVelocity;
			Yaw -= angularVelocity;
		}
		if (direction == LEFT)
		{
			AngleZ += angularVelocity;
			Yaw += angularVelocity;
		}
		if (direction == UP)
		{
			Pitch -= angularVelocity;
		}
		if (direction == DOWN)
		{
			Pitch += angularVelocity;
		}

		if (Distance < 1.0f)
			Distance = 1.0f;
		if (Pitch > 0.0f)
			Pitch = 0.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;

		float x = glm::cos(glm::radians(AngleZ)) * Distance;
		float z = glm::sin(glm::radians(AngleZ)) * Distance;
		float y = glm::sin(glm::radians(-Pitch)) * Distance;
		x *= glm::cos(glm::radians(-Pitch));
		z *= glm::cos(glm::radians(-Pitch));
		Position = glm::vec3(x, y, z);

		updateCameraVectors();
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors()
	{
		std::cout << "Camera position = " << Position.b << std::endl;

		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
};
#endif