#ifndef RAYH
#define RAYH
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

class Ray {
public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() {}
	Ray(glm::vec3 &origin_point, glm::vec3 &destination_point) {
		origin = origin_point;
		direction = glm::normalize(destination_point - origin_point);
	}

	// copy constructor
	Ray(Ray &ray) {
		origin = ray.origin;
		direction = ray.direction;
	}

	// assignment
	void operator=(Ray &ray) {
		origin = ray.origin;
		direction = ray.direction;
	}
	
	glm::vec3 PointAlongRay(const float t) const {
		glm::vec3 point = origin + t * direction;
		return point;
	}
};

#endif