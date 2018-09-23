#include <cassert>

#include "Steering.h"
#include "WanderAndChase.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "GraphicsSystem.h"

# define M_PI 3.14159265358979323846  /* pi */

WanderAndChase::WanderAndChase(const UnitID& ownerID, const Vector2D& targetLoc, float stopRad, float slowRad, float wanderRad, const UnitID& targetID):Steering(){
	mType = Steering::WANDERCHASE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	setRadius(wanderRad);
	setStopRadius(stopRad);
	setSlowRadius(slowRad);
	isChasing = true;
}

Steering* WanderAndChase::getSteering(){
	float targetRot;
	float stopRadAcc = .1;
	float slowRadAcc = .5;
	Vector2D direction, targetLoc;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?

	float targetTime = 1;

	if(mTargetID != INVALID_UNIT_ID){
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		targetLoc = pTarget->getPositionComponent()->getPosition();
	}

	if((targetLoc - pOwner->getPositionComponent()->getPosition()).getLength() <= rad){
		isChasing = true;
		if(targetLoc != ZERO_VECTOR2D){
			mTargetLoc = targetLoc;
		}
		direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
		float distance = direction.getLength();

		PhysicsData data = pOwner->getPhysicsComponent()->getData();

		//Do the rotation then stop
		Vector2D newDir = direction;
		newDir.normalize();

		newDir *= pOwner->getMaxAcc();
		float pTargetDest = atan2(newDir.getX(), newDir.getY());
		pTargetDest = M_PI - pTargetDest;

		float pOwnerDest = pOwner->getFacing();

		if(pOwnerDest > 2 * M_PI){
			pOwnerDest = fmod(pOwnerDest, 2 * M_PI);
		}

		float rotation = pTargetDest - pOwnerDest;

		float rotationSize = abs(rotation);

		if(rotationSize <= stopRadAcc){
			data.rotAcc = 0;
			data.rotVel = 0;
			this->mData = data;
		}

		if(rotationSize > slowRadAcc){
			targetRot = data.maxRotAcc;
		}
		else {
			targetRot = data.maxRotVel * rotationSize / slowRadAcc;
		}

		targetRot *= rotation / rotationSize;

		data.rotAcc	= targetRot - data.rotAcc;
		data.rotAcc /= targetTime;

		if(abs(data.rotAcc) > data.maxRotAcc){
			data.rotAcc /= abs(data.rotAcc);
			data.rotAcc += data.maxRotAcc;
		}

		//If we have arrived stop
		if(distance < stopRad){
			data.acc = ZERO_VECTOR2D;
			data.vel = ZERO_VECTOR2D;
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

	else {
		//If we were chasing before then recaculate a new position to wander
		if(isChasing){
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
			isChasing = false;
		}

		direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
		float distance = direction.getLength();

		PhysicsData data = pOwner->getPhysicsComponent()->getData();
		//If we have arrived stop
		if(distance < 25){
			int x = gpGame->getUnitManager()->getUnit(mOwnerID)->getPositionComponent()->getPosition().getX() + rad * genRandomBinomial();
			int y = gpGame->getUnitManager()->getUnit(mOwnerID)->getPositionComponent()->getPosition().getY() + rad * genRandomBinomial();
			if (x > gpGame->getGraphicsSystem()->getWidth()){
				x = gpGame->getGraphicsSystem()->getWidth() - 5;
			}
			if (y > gpGame->getGraphicsSystem()->getHeight()){
				y = gpGame->getGraphicsSystem()->getHeight() - 5;
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
		float pTargetDest = atan2(direction.getX(), direction.getY());
		pTargetDest = M_PI - pTargetDest;

		float pOwnerDest = pOwner->getFacing();

		if(pOwnerDest > 2 * M_PI){
			pOwnerDest = fmod(pOwnerDest, 2 * M_PI);

			float rotation = pTargetDest - pOwnerDest;

			float rotationSize = abs(rotation);

			if(rotationSize <= stopRadAcc){
				data.rotAcc = 0;
				data.rotVel = 0;
				this->mData = data;
			}

			if(rotationSize > slowRadAcc){
				targetRot = data.maxRotAcc;
			}
			else {
				targetRot = data.maxRotVel * rotationSize / slowRadAcc;
			}

			targetRot *= rotation / rotationSize;

			data.rotAcc	= targetRot - data.rotAcc;
			data.rotAcc /= targetTime;

			if(abs(data.rotAcc) > data.maxRotAcc){
				data.rotAcc /= abs(data.rotAcc);
				data.rotAcc += data.maxRotAcc;
			}
		}
		this->mData = data;
		return this;
	}
}