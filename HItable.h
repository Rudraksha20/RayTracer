#pragma once
#include "Ray.h"

// Object that stores the components of the surface that was hit
struct HitObjectRecord {
	float t;
	glm::vec3 Point;
	glm::vec3 normal;
};

class Hitable {
public:
	virtual bool CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord &record) const = 0;
};