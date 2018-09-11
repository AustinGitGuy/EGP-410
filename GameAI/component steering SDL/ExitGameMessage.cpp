#include "Game.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"
#include "UnitManager.h"

ExitGameMessage::ExitGameMessage(const bool& doExit)
	:GameMessage(PLAYER_MOVETO_MESSAGE)
	, exit(doExit)
{}

ExitGameMessage::~ExitGameMessage(){}

void ExitGameMessage::process(){
	gpGame->mShouldExit = exit;
}
