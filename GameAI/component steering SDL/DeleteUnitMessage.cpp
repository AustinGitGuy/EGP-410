#include "Game.h"
#include "GameMessageManager.h"
#include "DeleteUnitMessage.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "Unit.h"

DeleteUnitMessage::DeleteUnitMessage() : GameMessage(PLAYER_MOVETO_MESSAGE){}

DeleteUnitMessage::~DeleteUnitMessage(){}

void DeleteUnitMessage::process(){
	gpGame->getUnitManager()->deleteRandomUnit();
}
