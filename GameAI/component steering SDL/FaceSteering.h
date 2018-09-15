#pragma once
#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering {
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	void setRadius(const float& radius) { rad = radius; };
protected:
	virtual Steering* getSteering();
	float rad;
};