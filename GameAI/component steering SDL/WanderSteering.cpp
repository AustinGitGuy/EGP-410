#include <cassert>

#include "Steering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "GraphicsSystem.h"

# define M_PI 3.14159265358979323846  /* pi */

WanderSteering::WanderSteering(const UnitID& ownerID, float radius, const UnitID& targetID):Steering(){
	int x = gpGame->getUnitManager()->getUnit(ownerID)->getPositionComponent()->getPosition().getX() + radius * genRandomBinomial();
	int y = gpGame->getUnitManager()->getUnit(ownerID)->getPositionComponent()->getPosition().getY() + radius * genRandomBinomial();
	if(x > gpGame->getGraphicsSystem()->getWidth() - 25){
		x = x % gpGame->getGraphicsSystem()->getWidth();
	}
	if(y > gpGame->getGraphicsSystem()->getHeight() - 25){
		y = y % gpGame->getGraphicsSystem()->getHeight();
	}
	const Vector2D pos = Vector2D(x, y);
	mType = Steering::WANDER;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(pos);
	setRadius(radius);
}

Steering* WanderSteering::getSteering(){
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
	if(distance < 25){
		int x = gpGame->getUnitManager()->getUnit(mOwnerID)->getPositionComponent()->getPosition().getX() + rad * genRandomBinomial();
		int y = gpGame->getUnitManager()->getUnit(mOwnerID)->getPositionComponent()->getPosition().getY() + rad * genRandomBinomial();
		if (x > gpGame->getGraphicsSystem()->getWidth()) {
			x = x % gpGame->getGraphicsSystem()->getWidth();
		}
		if (y > gpGame->getGraphicsSystem()->getHeight()) {
			y = y % gpGame->getGraphicsSystem()->getHeight();
		}
		const Vector2D pos = Vector2D(x, y);
		setTargetLoc(pos);
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
	
	direction.normalize();
	direction *= pOwner->getMaxAcc();
	float velocityDirection = atan2(direction.getX(), direction.getY());
	pOwner->getPositionComponent()->setFacing((M_PI) - velocityDirection);

	this->mData = data;
	return this;
}