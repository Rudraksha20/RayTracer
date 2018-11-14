#ifndef SPHEREH
#define SPHEREH
#include "Hitable.h"

class Sphere: public Hitable{
public:
	float radius;
	glm::vec3 center;

	Sphere() {}
	Sphere(float r, glm::vec3 c) : radius(r), center(c) {}

	virtual bool CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord *record) const override;

	~Sphere() {}
};

bool Sphere::CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord *record) const {
	// Logic to check if the ray hit the sphere
	glm::vec3 oc = ray.origin - center;
	float a = glm::dot(ray.direction, ray.direction);
	float b = glm::dot(oc, ray.direction);
	float c = glm::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - glm::sqrt(discriminant)) / (a);
		if (temp < tMax && temp > tMin) {
			glm::vec3 point = ray.PointAlongRay(temp);
			glm::vec3 normal = glm::normalize((point - center) / radius);
			record->t = temp;
			record->Point = point;
			record->normal = normal;
			//record = new HitObjectRecord(temp, point, normal);			
			return true;
		}
		temp = (-b + glm::sqrt(discriminant)) / a;
		if (temp < tMax && temp > tMin) {
			glm::vec3 point = ray.PointAlongRay(temp);
			glm::vec3 normal = glm::normalize((point - center) / radius);
			record->t = temp;
			record->Point = point;
			record->normal = normal;
			//record = new HitObjectRecord(temp, point, normal);
			return true;
		}
	}

	return false;
}

#endif