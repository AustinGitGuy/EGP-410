#include "Cohesion.h"
#include "Unit.h"
#include "UnitManager.h"
#include "Game.h"

Cohesion::Cohesion(const UnitID& ownerID, float distUnits){
	mType = Steering::COHESION;
	setOwnerID(ownerID);
	setUnitDist(distUnits);
}

Steering* Cohesion::getSteering(){
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	Vector2D pos = ZERO_VECTOR2D;
	int neighborNum = 0;
	for (auto it = gpGame->getUnitManager()->mUnitMap.begin(); it != gpGame->getUnitManager()->mUnitMap.end(); ++it){
		if(it->first != mOwnerID && it->second != NULL){
			float distance;
			distance = (it->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition()).getLength();
			if(distance < unitDist){
				neighborNum++;
				pos += it->second->getPositionComponent()->getPosition();
			}
		}
	}
	if(neighborNum != 0){
		pos /= neighborNum;
		data.acc = pos - pOwner->getPositionComponent()->getPosition();
	}
	else {
		data.acc = ZERO_VECTOR2D;
		data.vel = ZERO_VECTOR2D;
		data.rotVel = 0;
	}
	this->mData = data;
	return this;
}