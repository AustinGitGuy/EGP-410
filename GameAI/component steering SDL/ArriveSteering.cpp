#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

# define M_PI 3.14159265358979323846  /* pi */

ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, float stopRadius, float slowRadius, const UnitID& targetID):Steering(){
	mType = Steering::ARRIVE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	setStopRadius(stopRadius);
	setSlowRadius(slowRadius);
}

Steering* ArriveSteering::getSteering(){
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?

	float targetTime = 1;

	if(mTargetID != INVALID_UNIT_ID){
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	float distance = direction.getLength();

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//If we have arrived stop
	if(distance < stopRad){
		data.acc = ZERO_VECTOR2D;
		data.vel = ZERO_VECTOR2D;
		data.rotVel = 0;
		this->mData = data;
		return this;
	}

	//Since speed is just the magnitude of velocity, create a variable here then multiply later on.
	float speed;
	if(distance > slowRad){
		speed = data.maxSpeed;
	}
	else {
		speed = data.maxSpeed * distance / slowRad;
	}

	Vector2D targetVel = direction;
	targetVel.normalize();
	targetVel *= speed;

	Vector2D targetAcc = targetVel - data.vel;
	targetAcc /= targetTime;

	if(targetAcc.getLength() > data.maxAccMagnitude){
		targetAcc.normalize();
		targetAcc += data.maxAccMagnitude;
	}

	data.acc = targetAcc;

	this->mData = data;
	return this;
}