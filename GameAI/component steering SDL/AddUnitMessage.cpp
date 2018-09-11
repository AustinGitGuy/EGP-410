#include "Game.h"
#include "GameMessageManager.h"
#include "AddUnitMessage.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "Unit.h"

AddUnitMessage::AddUnitMessage():GameMessage(PLAYER_MOVETO_MESSAGE){}

AddUnitMessage::~AddUnitMessage() {}

void AddUnitMessage::process(){
	Unit* pUnit = gpGame->getUnitManager()->createRandomUnit(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID));
}
