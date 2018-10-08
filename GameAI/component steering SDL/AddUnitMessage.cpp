#include "Game.h"
#include "GameMessageManager.h"
#include "AddUnitMessage.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "Unit.h"

AddUnitMessage::AddUnitMessage(int num):GameMessage(ADD_UNIT_MESSAGE){numUnits = num;}

AddUnitMessage::~AddUnitMessage() {}

void AddUnitMessage::process(){
	gpGame->getUnitManager()->createBoidFlock(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), numUnits);
}
