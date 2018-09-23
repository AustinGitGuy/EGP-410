#include <Trackable.h>
#include "Steering.h"

class ArriveAndFace : public Steering {
public:
	ArriveAndFace(const UnitID& ownerID, const Vector2D& targetLoc, float stopRadius, float arriveRadius, const UnitID& targetID = INVALID_UNIT_ID);
	void setStopRadius(const float& radius) { stopRad = radius; };
	void setSlowRadius(const float& radius) { slowRad = radius; };
protected:
	virtual Steering* getSteering();
	float stopRad, slowRad;
};