#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering {
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, float radius, const UnitID& targetID = INVALID_UNIT_ID);
	void setRadius(const float& radius) { rad = radius; };
protected:
	virtual Steering* getSteering();
	float rad;
};