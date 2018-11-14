#ifndef METALH
#define METALH
#pragma once
#include "Material.h"
#include "Utilities.h"

class Material;

class Metal : public Material {
public:
	// Base color of the metallic object
	glm::vec3 albedo;

	Metal(glm::vec3 a) : albedo(a) {}

	bool Scatter(Ray &rayI, HitObjectRecord *record, glm::vec3 attenuation, Ray &rayScattered) const override{
		glm::vec3 rayReflected = Utilities::Reflect(glm::normalize(rayI.direction) , record->normal);
		rayScattered = Ray(record->Point, rayReflected);
		attenuation = albedo;
		return (dot(rayScattered.direction, record->normal) > 0.0f);
	}

	~Metal() {
		// Cleanup
	}
};

#endif