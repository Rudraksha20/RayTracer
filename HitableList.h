#pragma once
#include "Hitable.h"
#include <vector>

class HitableList : public Hitable {
public:
	std::vector<Hitable*> hitableObjectList;

	HitableList() {}
	HitableList(std::vector<Hitable*> HL) : hitableObjectList(HL) {}
	virtual bool CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord &record) const;
};