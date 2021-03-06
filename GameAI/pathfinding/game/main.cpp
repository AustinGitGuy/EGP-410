/*main.cpp
	*
	*	Dean Lawson
	*	Champlain College
	*	2011
	*
	*/
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>

#include <SDL.h>

#include "Game.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Defines.h"
#include <Timer.h>
#include <MemoryTracker.h>
#include <PerformanceTracker.h>

PerformanceTracker* gpPerformanceTracker = NULL;

int main(int argc, char **argv){
	gpPerformanceTracker = new PerformanceTracker();

	gpGame = new GameApp();

	gpGame->Init();

	bool shouldExit = false;

	while(!shouldExit){
		gpGame->BeginLoop();
		gpGame->ProcessLoop();
		shouldExit = gpGame->EndLoop();
	}

	//Cleanup
	gpGame->Cleanup();
	delete gpGame;
	delete gpPerformanceTracker;

	MemoryTracker::getInstance()->reportAllocations(std::cout);

	system("pause");

	return 0;
}

