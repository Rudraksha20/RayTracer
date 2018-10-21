#pragma once
#include "Ray.h"

class Camera {
public:
	// Camera origin
	glm::vec3 cameraOrigin;
	// Screen vectors
	glm::vec3 lowerLeftCorner;
	glm::vec3 horizontal;
	glm::vec3 vertical;

	Camera() {
		// Camera origin
		cameraOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
		// Screen vectors
		lowerLeftCorner = glm::vec3(-2.0f, -1.0f, -1.0f);
		horizontal = glm::vec3(4.0f, 0.0f, 0.0f);
		vertical = glm::vec3(0.0f, 2.0f, 0.0f);
	}

	Ray GenerateRay(float u, float v) {
		Ray ray(cameraOrigin, lowerLeftCorner + u * horizontal + v * vertical);
		return ray;
	}
};