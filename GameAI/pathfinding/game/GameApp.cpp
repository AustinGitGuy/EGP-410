#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include <Vector2D.h>
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "DepthFirstPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "DijkstraPathfinder.h"
#include "InputManager.h"
#include "AStar.h"

#include <SDL.h>
#include <fstream>
#include <vector>

const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "pathgrid.txt";

GameApp::GameApp():messageManager(NULL),grid(NULL),gridGraph(NULL),gridPathfinder(NULL),debugDisplay(NULL){}

GameApp::~GameApp(){
	Cleanup();
}

bool GameApp::Init(){
	bool retVal = Game::Init();
	if(!retVal){
		return false;
	}

	messageManager = new GameMessageManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	grid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	gridVisualizer = new GridVisualizer(grid);
	std::ifstream theStream(gFileName);
	grid->load(theStream);

	//create the GridGraph for pathfinding
	gridGraph = new GridGraph(grid);
	//Init the nodes and connections
	gridGraph->init();

	gridPathfinder = new AStar(gridGraph);

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer(mBackgroundBufferID);
	if(pBackGroundBuffer != NULL){
		mpSpriteManager->createAndManageSprite(BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight());
	}

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent(gridPathfinder);
	debugDisplay = new DebugDisplay(Vector2D(0,12), pContent);

	mpMasterTimer->start();
	return true;
}

void GameApp::Cleanup(){
	delete messageManager;
	messageManager = NULL;

	delete grid;
	grid = NULL;

	delete gridVisualizer;
	gridVisualizer = NULL;

	delete gridGraph;
	gridGraph = NULL;

	delete gridPathfinder;
	gridPathfinder = NULL;

	delete debugDisplay;
	debugDisplay = NULL;
}

void GameApp::BeginLoop(){
	//should be the first thing done
	Game::BeginLoop();
}

void GameApp::ProcessLoop(){
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	gridVisualizer->Draw(*pBackBuffer);
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	gridPathfinder->DrawVisualization(grid, pBackBuffer);
#endif

	debugDisplay->Draw(pBackBuffer);
	inputManager->Update();
	messageManager->ProcessMessagesForThisFrame();

	//should be last thing in ProcessLoop
	Game::ProcessLoop();
}

bool GameApp::EndLoop(){
	return Game::EndLoop();
}
