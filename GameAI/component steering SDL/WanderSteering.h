#include <Trackable.h>
#include "Steering.h"

class WanderSteering : public Steering {
public:
	WanderSteering(const UnitID& ownerID, float radius, const UnitID& targetID = INVALID_UNIT_ID);
	void setRadius(const float& radius) { rad = radius; };
protected:
	virtual Steering* getSteering();
	float rad;
};