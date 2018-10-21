#include "Sphere.h"

bool Sphere::CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord &record) const {
	// Logic to check if the ray hit the sphere
	glm::vec3 oc = ray.origin - center;
	float a = glm::dot(ray.direction, ray.direction);
	float b = glm::dot(oc, ray.direction);
	float c = glm::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if(discriminant > 0) {
		float temp = (-b - glm::sqrt(discriminant)) / (a);
		if (temp < tMax && temp > tMin) {
			record.t = temp;
			record.Point = ray.PointAlongRay(temp);
			record.normal = (record.Point - center) / radius;
			return true;
		}
		temp = (-b + glm::sqrt(discriminant)) / a;
		if (temp < tMax && temp > tMin) {
			record.t = temp;
			record.Point = ray.PointAlongRay(temp);
			record.normal = (record.Point - center) / radius;
			return true;
		}
	}

	return false;
}