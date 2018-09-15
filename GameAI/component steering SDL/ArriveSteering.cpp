#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

# define M_PI 3.14159265358979323846  /* pi */

ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, float radius, const UnitID& targetID):Steering(){
	mType = Steering::ARRIVE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	setRadius(radius);
}

Steering* ArriveSteering::getSteering(){
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?

	if(mTargetID != INVALID_UNIT_ID){
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();

	if(diff.getLength() < rad){
		PhysicsData data = pOwner->getPhysicsComponent()->getData();
		data.acc = ZERO_VECTOR2D;
		data.vel = ZERO_VECTOR2D;
		data.rotVel = 0;
		this->mData = data;
		return this;
	}
	
	diff.normalize();
	diff *= pOwner->getMaxAcc();
	float velocityDirection = atan2(diff.getX(), diff.getY());
	pOwner->getPositionComponent()->setFacing((M_PI) - velocityDirection);

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.acc = diff;
	data.rotVel = .5f;
	this->mData = data;
	return this;
}