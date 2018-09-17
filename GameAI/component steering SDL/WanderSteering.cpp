#include <cassert>

#include "Steering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "GraphicsSystem.h"

# define M_PI 3.14159265358979323846  /* pi */

WanderSteering::WanderSteering(const UnitID& ownerID, float radius, const UnitID& targetID):Steering(){
	float x = gpGame->getUnitManager()->getUnit(ownerID)->getPositionComponent()->getPosition().getX() + radius * genRandomBinomial();
	float y = gpGame->getUnitManager()->getUnit(ownerID)->getPositionComponent()->getPosition().getY() + radius * genRandomBinomial();
	if(x > gpGame->getGraphicsSystem()->getWidth()){
		x = gpGame->getGraphicsSystem()->getWidth() - 20;
	}
	if(y > gpGame->getGraphicsSystem()->getHeight()){
		y = gpGame->getGraphicsSystem()->getHeight() - 20;
	}
	const Vector2D pos = Vector2D(x, y);
	mType = Steering::ARRIVE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(pos);
	setRadius(radius);
}

Steering* WanderSteering::getSteering(){
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?

	float targetTime = 0.1f;

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
	if(distance < 5){
		data.acc = ZERO_VECTOR2D;
		data.vel = ZERO_VECTOR2D;
		data.rotVel = 0;
		this->mData = data;
		return this;
	}
	float speed = data.maxSpeed;

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
	data.vel = targetVel;

	direction.normalize();
	direction *= pOwner->getMaxAcc();
	float velocityDirection = atan2(direction.getX(), direction.getY());
	pOwner->getPositionComponent()->setFacing((M_PI) - velocityDirection);

	this->mData = data;
	return this;
}