#include "Steering.h"
#include "Trackable.h"

class Flocking: public Steering {
public:
	Flocking(const UnitID& ownerID, float distUnits);
	~Flocking();
	void setUnitDist(const float& distUnits) { unitDist = distUnits; };
	void setSepWeight(const float& sepWeight){seperationWeight = sepWeight;};
	void setAlignWeight(const float& alignWeight){alignmentWeight = alignWeight;};
	void setCohesionWeight(const float& cohereWeight){cohesionWeight = cohereWeight;};
	void setWanderWeight(const float& wandWeight){wanderWeight = wandWeight;};

private:
	virtual Steering* getSteering();
	float unitDist;
	float seperationWeight = .5f;
	float alignmentWeight = .6f;
	float cohesionWeight = .3f;
	float wanderWeight = .4f;
};