#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering {
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, float stopRadius, float arriveRadius, const UnitID& targetID = INVALID_UNIT_ID);
	void setStopRadius(const float& radius) { stopRad = radius; };
	void setSlowRadius(const float& radius) { slowRad = radius; };
protected:
	virtual Steering* getSteering();
	float stopRad, slowRad;
};