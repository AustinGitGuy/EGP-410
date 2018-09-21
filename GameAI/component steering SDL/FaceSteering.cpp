#include <cassert>

#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include <math.h>

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
	float targetRot;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?

	float timeToTarget = 1;

	if(mTargetID != INVALID_UNIT_ID){
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	Vector2D direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();

	direction.normalize();
	direction *= pOwner->getMaxAcc();
	float pTargetDest = atan2(direction.getX(), direction.getY());
	pTargetDest = M_PI - pTargetDest;

	float pOwnerDest = pOwner->getFacing();

	if(pOwnerDest > 2 * M_PI){
		pOwnerDest = fmod(pOwnerDest, 2 * M_PI);
	}

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	float rotation = pTargetDest - pOwnerDest;

	float rotationSize = abs(rotation);

	if(rotationSize <= stopRad){
		data.rotAcc = 0;
		data.rotVel = 0;
		this->mData = data;
	}

	if(rotationSize > slowRad){
		targetRot = data.maxRotAcc;
	}
	else {
		targetRot = data.maxRotVel * rotationSize / slowRad;
	}

	targetRot *= rotation / rotationSize;

	data.rotAcc	= targetRot - data.rotAcc;
	data.rotAcc /= timeToTarget;

	if(abs(data.rotAcc) > data.maxRotAcc){
		data.rotAcc /= abs(data.rotAcc);
		data.rotAcc += data.maxRotAcc;
	}

	this->mData = data;

	return this;
}