#ifndef MATERIALH
#define MATERIALH
#pragma once
#include "Ray.h"
#include "Hitable.h"
#include <glm/vec3.hpp>

class HitObjectRecord;

class Material {
public:
	virtual bool Scatter(Ray &rayI, HitObjectRecord *record, glm::vec3 attenuation, Ray &rayScattered) const;

	virtual ~Material();
};

#endif