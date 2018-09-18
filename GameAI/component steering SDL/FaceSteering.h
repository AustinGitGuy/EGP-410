#pragma once
#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering {
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, float stopRadius, float slowRadius, const UnitID& targetID = INVALID_UNIT_ID);
	void setStopRadius(const float& radius) { stopRad = radius; };
	void setSlowRadius(const float& radius) { slowRad = radius; };
protected:
	virtual Steering* getSteering();
	float slowRad;
	float stopRad;
};