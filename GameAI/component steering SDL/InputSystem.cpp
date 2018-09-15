#include <SDL.h>
#include <stdio.h>
#include <Vector2D.h>
#include "Game.h"
#include "InputSystem.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "ExitGameMessage.h"
#include "AddUnitMessage.h"
#include "DeleteUnitMessage.h"

InputSystem::InputSystem(){}

InputSystem::~InputSystem(){}

void InputSystem::Update(){
	SDL_PumpEvents();
	int x, y;
	SDL_GetMouseState(&x, &y);

	SDL_PumpEvents();
	if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)){
		Vector2D pos(x, y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	//get keyboard state
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	//if escape key was down then exit the loop
	if(state[SDL_SCANCODE_ESCAPE]){
		GameMessage* pMessage = new ExitGameMessage(true);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	//If return is pressed add a unit
	if(state[SDL_SCANCODE_RETURN]){
		GameMessage* pMessage = new AddUnitMessage();
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if(state[SDL_SCANCODE_D]){
		GameMessage* pMessage = new DeleteUnitMessage();
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}
}