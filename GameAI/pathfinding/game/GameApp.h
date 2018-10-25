#pragma once

/*Game - class to hold all game related info.

Dean Lawson
Champlain College
2011
*/

#include "Game.h"

//forward declarations
class GraphicsBuffer;
class Sprite;
class KinematicUnit;
class GameMessageManager;
class Grid;
class GridVisualizer;
class GridGraph;
class GridPathfinder;
class DebugDisplay;
class InputManager;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame


class GameApp: public Game {
public:
	GameApp();
	~GameApp();

	virtual bool Init();
	virtual void Cleanup();

	//game loop
	virtual void BeginLoop();
	virtual void ProcessLoop();
	virtual bool EndLoop();

	//accessors
	inline GameMessageManager* GetMessageManager(){return messageManager;};
	inline GridVisualizer* GetGridVisualizer(){return gridVisualizer;};
	inline GridPathfinder* GetPathfinder(){return gridPathfinder;};
	inline DebugDisplay* GetDebugDisplay(){return debugDisplay;};
	inline Grid* GetGrid(){return grid;};
	inline GridGraph* GetGridGraph(){return gridGraph;};
	inline void SetDebugDisplay(DebugDisplay* newDebugDisplay){debugDisplay = newDebugDisplay;}; 
	inline void SetPathfinder(GridPathfinder* newPathfinder){gridPathfinder = newPathfinder;};
private:
	GameMessageManager* messageManager;
	Grid* grid;
	GridVisualizer* gridVisualizer;
	GridGraph* gridGraph;
	DebugDisplay* debugDisplay;
	InputManager* inputManager;
	GridPathfinder* gridPathfinder;

};

