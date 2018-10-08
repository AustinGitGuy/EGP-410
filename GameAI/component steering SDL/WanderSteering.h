#include <Trackable.h>
#include "Steering.h"

class WanderSteering : public Steering {
public:
	WanderSteering(const UnitID& ownerID, float radius);
	void setRadius(const float& radius) { rad = radius; };
	virtual Steering* getSteering();

protected:
	float rad;
};