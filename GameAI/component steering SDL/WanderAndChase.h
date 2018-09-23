#include <Trackable.h>
#include "Steering.h"

class WanderAndChase : public Steering {
public:
	WanderAndChase(const UnitID& ownerID, const Vector2D& targetLoc, float stopRad, float slowRad, float wanderRad, const UnitID& targetID = INVALID_UNIT_ID);
	void setRadius(const float& radius) { rad = radius; };
	void setStopRadius(const float& radius) { stopRad = radius; };
	void setSlowRadius(const float& radius) { slowRad = radius; };
protected:
	virtual Steering* getSteering();
	float rad, stopRad, slowRad;
	bool isChasing;
};