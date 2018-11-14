#ifndef UTILITIESH
#define UTILITIESH
#pragma once
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#define NumberOfThreads 6
#define EPSILON 0.00001f

class Utilities {
public:
	static float GetRandom() {
		return (rand() / (RAND_MAX + 1.0));
	}

	static float Vector3Length(const glm::vec3 point) {
		return glm::sqrt((point.x * point.x) + (point.y * point.y) + (point.z * point.z));
	}

	static float LengthSquare(const glm::vec3 point) {
		float l = Vector3Length(point);
		return l * l;
	}

	// Gamma correcting the color
	static glm::vec3 Gamma2(glm::vec3 color) {
		return glm::vec3(glm::sqrt(color.x), glm::sqrt(color.y), glm::sqrt(color.z));
	}

	static glm::vec3 RandomInUnitSphere() {
		glm::vec3 point;
		do {
			point = (2.0f * glm::vec3(GetRandom(), GetRandom(), GetRandom())) - 1.0f;
		} while ((LengthSquare(point)) >= 1.0f);

		return point;
	}

	// reflect the incidenr ray
	// the Ray is (incoming by convention) pointing into the surface away from the normal.
	// the reflected ray points outside the surface.
	static glm::vec3 Reflect(glm::vec3 rayIncident, glm::vec3 normal) {
		glm::vec3 rayReflected(rayIncident - 2.0f * glm::dot(rayIncident, normal) * normal);
		return glm::normalize(rayReflected);
	}

};

#endif