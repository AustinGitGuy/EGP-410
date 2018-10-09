#include <Trackable.h>
#include "Steering.h"

class ArriveAndFace : public Steering {
public:
	ArriveAndFace(const UnitID& ownerID, const Vector2D& targetLoc, float stopRadius, float slowRadius, const UnitID& targetID = INVALID_UNIT_ID);
	void setStopRadius(const float& radius) { stopRad = radius; };
	void setSlowRadius(const float& radius) { slowRad = radius; };
	virtual Steering* getSteering();

protected:
	float stopRad, slowRad;
};