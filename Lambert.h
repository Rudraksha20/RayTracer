#ifndef LAMBERTH
#define LAMBERTH
#pragma once
#include "Material.h"
#include "Utilities.h"

class Material;

class Lambert : public Material {
public:
	// Base color of the lambertian object
	glm::vec3 albedo;

	Lambert(glm::vec3 a) : albedo(a) {}

	bool Scatter(Ray &rayI, HitObjectRecord *record, glm::vec3 attenuation, Ray &rayScattered) const override{
		glm::vec3 target = record->Point + record->normal + Utilities::RandomInUnitSphere();
		rayScattered = Ray(record->Point, target);
		attenuation = albedo;
		return true;
	}

	~Lambert() {
		// Cleanup
	}
};

#endif