#ifndef HITABLEH
#define HITABLEH
#include "Ray.h"
#include <vector>
#include <glm/vec3.hpp>

// Object that stores the components of the surface that was hit
class HitObjectRecord {
public:

	HitObjectRecord() {}
	HitObjectRecord(float _t, glm::vec3 _Point, glm::vec3 _normal) : t(_t), Point(_Point), normal(_normal) {}

	float t;
	glm::vec3 Point;
	glm::vec3 normal;
};

class Hitable {
public:
	virtual bool CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord *record) const = 0;

	virtual ~Hitable() = 0;
};

Hitable::~Hitable() {

}

class HitableList : public Hitable {
public:
	std::vector<Hitable*> *hitableObjectList;

	HitableList() {}
	HitableList(std::vector<Hitable*> *HL) : hitableObjectList(HL) {}
	virtual bool CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord *record) const override;

	~HitableList() {
		// Memory management
		delete hitableObjectList;
		hitableObjectList = 0;
	}
};

bool HitableList::CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord *record) const {
	// Iterate through all the objects and check for a hit
	bool hitSomething = false;
	double closesSoFar = tMax;
	for (int i = 0; i < (*hitableObjectList).size(); i++) {
		bool anObjectWasHit = (*hitableObjectList)[i]->CheckObjectHit(ray, tMin, closesSoFar, record);
		if (anObjectWasHit == true) {
			hitSomething = true;
			//record = tempObjHitPtr;
			closesSoFar = record->t;
		}
	}
	return hitSomething;
}

#endif