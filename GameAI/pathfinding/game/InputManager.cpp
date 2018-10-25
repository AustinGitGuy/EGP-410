#include "InputManager.h"
#include "SDL.h"
#include "GameMessageManager.h"
#include "Game.h"
#include "GameApp.h"
#include "Vector2D.h"
#include "PathToMessage.h"
#include "GridPathfinder.h"
#include "DijkstraPathfinder.h"
#include "DepthFirstPathfinder.h"
#include "AStar.h"
#include "GridGraph.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "GridPathfinder.h"

InputManager::InputManager(){}

InputManager::~InputManager(){}

void InputManager::Update(){
	int x, y;
	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	SDL_PumpEvents();

	//get keyboard state
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	GameApp* gamio = dynamic_cast<GameApp*>(gpGame);

	if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)){
		static Vector2D lastPos(0.0f, 0.0f);
		Vector2D pos(x,y);
		if(lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY()){
			GameMessage* pMessage = new PathToMessage(lastPos, pos);
			gamio->GetMessageManager()->AddMessage(pMessage, 0);
			lastPos = pos;
		}
	}

	if(state[SDL_SCANCODE_F]){
		delete gamio->GetPathfinder();
		delete gamio->GetDebugDisplay();
		gamio->SetPathfinder(new DepthFirstPathfinder(gamio->GetGridGraph()));
		gamio->SetDebugDisplay(new DebugDisplay(Vector2D(0,12), new PathfindingDebugContent(gamio->GetPathfinder())));
	}

	if(state[SDL_SCANCODE_D]){
		delete gamio->GetPathfinder();
		delete gamio->GetDebugDisplay();
		gamio->SetPathfinder(new DijkstraPathfinder(gamio->GetGridGraph()));
		gamio->SetDebugDisplay(new DebugDisplay(Vector2D(0,12), new PathfindingDebugContent(gamio->GetPathfinder())));
	}

	if(state[SDL_SCANCODE_A]){
		delete gamio->GetPathfinder();
		delete gamio->GetDebugDisplay();
		gamio->SetPathfinder(new AStar(gamio->GetGridGraph()));
		gamio->SetDebugDisplay(new DebugDisplay(Vector2D(0,12), new PathfindingDebugContent(gamio->GetPathfinder())));
	}

	//if escape key was down then exit the loop
	if(state[SDL_SCANCODE_ESCAPE]){
		gamio->markForExit();
	}
}