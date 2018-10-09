#pragma once
#include "ComponentManager.h"
#include "SteeringComponent.h"
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "WanderSteering.h"
#include "WanderAndChase.h"
#include "ArriveAndFace.h"
#include "Alignment.h"
#include "Cohesion.h"
#include "Seperation.h"
#include "Flocking.h"

SteeringComponent::SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID) 
	:Component(id)
	, mPhysicsComponentID(physicsComponentID)
	, mpSteering(NULL)
{
}

SteeringComponent::~SteeringComponent()
{
	delete mpSteering;
}

void SteeringComponent::applySteering(PhysicsComponent& physicsComponent)
{
	if (mpSteering != NULL)
	{
		//allow Steering to run
		mpSteering->update();
		//set physics data to that of the Steering
		physicsComponent.setData(mpSteering->getData());
		//update component's data
		mData.targetLoc = mpSteering->getTargetLoc();
	}
}

void SteeringComponent::setData(const SteeringData& data){
	mData = data;

	switch (data.type){
		case Steering::SEEK: {
			//cleanup old steering - todo: check for already existing steering and reuse if possible
			delete mpSteering;
			//create new steering
			mpSteering = new SeekSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::FLEE: {
			mpSteering = new SeekSteering(data.ownerID, data.targetLoc, data.targetID, true);
			break;
		}
		case Steering::ARRIVE: {
			delete mpSteering;
			mpSteering = new ArriveSteering(data.ownerID, data.targetLoc, 10, 150, data.targetID);
			break;
		}
		case Steering::FACE: {
			delete mpSteering;
			mpSteering = new FaceSteering(data.ownerID, data.targetLoc, .1, .5, data.targetID);
			break;
		}
		case Steering::WANDER: {
			delete mpSteering;
			mpSteering = new WanderSteering(data.ownerID, 250);
			break;
		}
		case Steering::WANDERCHASE: {
			delete mpSteering;
			mpSteering = new WanderAndChase(data.ownerID, data.targetLoc, 10, 150, 250, data.targetID);
			break;
		}
		case Steering::ARRIVEFACE: {
			delete mpSteering;
			mpSteering = new ArriveAndFace(data.ownerID, data.targetLoc, 10, 150, data.targetID);
			break;
		}
		case Steering::ALIGNMENT: {
			delete mpSteering;
			mpSteering = new Alignment(data.ownerID, 150);
			break;
		}
		case Steering::COHESION: {
			delete mpSteering;
			mpSteering = new Cohesion(data.ownerID, 150);
			break;
		}
		case Steering::SEPERATION: {
			delete mpSteering;
			mpSteering = new Seperation(data.ownerID, 150);
			break;
		}
		case Steering::FLOCKING: {
			delete mpSteering;
			mpSteering = new Flocking(data.ownerID, 150);
			break;
		}
		default: {

		}
	};
}

