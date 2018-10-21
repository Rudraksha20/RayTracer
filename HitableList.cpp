#include "HitableList.h"

bool HitableList::CheckObjectHit(const Ray &ray, float tMin, float tMax, HitObjectRecord &record) const {
	// Iterate through all the objects and check for a hit
	HitObjectRecord tempObjectHitRecord;
	bool hitSomething = false;
	double closesSoFar = tMax;
	for (int i = 0; i < hitableObjectList.size(); i++) {
		if (hitableObjectList[i]->CheckObjectHit(ray, tMin, closesSoFar, tempObjectHitRecord)) {
			hitSomething = true;
			closesSoFar = tempObjectHitRecord.t;
			record = tempObjectHitRecord;
		}
	}
	return hitSomething;
}