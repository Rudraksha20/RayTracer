#pragma once
#include "Hitable.h"

class Sphere: public Hitable{
public:
	float radius;
	glm::vec3 center;

	Sphere() {}
	Sphere(float r, glm::vec3 c) : radius(r), center(c) {}

	virtual bool CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord &record) const;
};