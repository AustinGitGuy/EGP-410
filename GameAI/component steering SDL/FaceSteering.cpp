#include <cassert>

#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

# define M_PI 3.14159265358979323846  /* pi */

FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, float stopRadius, float slowRadius, const UnitID& targetID):Steering(){
	mType = Steering::FACE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	setSlowRadius(slowRadius);
	setStopRadius(stopRadius);
}

Steering* FaceSteering::getSteering(){
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?

	float timeToTarget = 1;

	if(mTargetID != INVALID_UNIT_ID){
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();

	diff.normalize();
	diff *= pOwner->getMaxAcc();
	float rotation = atan2(diff.getX(), diff.getY());
	rotation = (M_PI) - rotation;

	if(rotation > M_PI){
		rotation -= M_PI;
	}

	float rotationSize = abs(rotation);

	if(rotation <= stopRad){
		data.rotAcc = 0;
		data.rotVel = 0;
		this->mData = data;
	}
	
	float targetRot;

	if(rotation > slowRad){
		targetRot = data.maxRotVel;
	}
	else {
		targetRot = data.maxRotVel * rotationSize / slowRad;
	}

	return this;
}