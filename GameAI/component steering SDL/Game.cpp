#include <stdio.h>
#include <assert.h>

#include <sstream>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include "GraphicsBufferManager.h"
#include "GameMessageManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "PlayerMoveToMessage.h"
#include "ComponentManager.h"
#include "UnitManager.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;
const Uint32 MAX_UNITS = 100;

Game::Game()
	:mpGraphicsSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mpFont(NULL)
	,mShouldExit(false)
	,mBackgroundBufferID("")
	,mpMessageManager(NULL)
	,mpComponentManager(NULL)
	,mpUnitManager(NULL)
{}

Game::~Game(){
	cleanup();
}

bool Game::init(){
	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->init( WIDTH, HEIGHT );
	if(!goodGraphics){
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager(mpGraphicsSystem);
	mpSpriteManager = new SpriteManager();


	mpMessageManager = new GameMessageManager();
	mpComponentManager = new ComponentManager(MAX_UNITS);
	mpUnitManager = new UnitManager(MAX_UNITS);

	inSys = new InputSystem();

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID,"wallpaper.bmp");
	mpGraphicsBufferManager->loadBuffer(mPlayerIconBufferID,"arrow.png");
	mpGraphicsBufferManager->loadBuffer(mEnemyIconBufferID,"enemy-arrow.png");
	mpGraphicsBufferManager->loadBuffer(mTargetBufferID,"target.png");

	//load Font
	mpFont = new Font("cour.ttf", 24);
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer(mBackgroundBufferID);
	if(pBackGroundBuffer != NULL){
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer(mPlayerIconBufferID);
	Sprite* pArrowSprite = NULL;
	if(pPlayerBuffer != NULL){
		pArrowSprite = mpSpriteManager->createAndManageSprite( PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, (float)pPlayerBuffer->getWidth(), (float)pPlayerBuffer->getHeight() );
	}
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer(mEnemyIconBufferID);
	Sprite* pEnemyArrow = NULL;
	if(pAIBuffer != NULL){
		pEnemyArrow = mpSpriteManager->createAndManageSprite(AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, (float)pAIBuffer->getWidth(), (float)pAIBuffer->getHeight());
	}

	GraphicsBuffer* pTargetBuffer = mpGraphicsBufferManager->getBuffer(mTargetBufferID);
	if(pTargetBuffer != NULL){
		mpSpriteManager->createAndManageSprite(TARGET_SPRITE_ID, pTargetBuffer, 0, 0, (float)pTargetBuffer->getWidth(), (float)pTargetBuffer->getHeight());
	}

	//setup units
	//Unit* pUnit = mpUnitManager->createPlayerUnit(*pArrowSprite);
	//pUnit->setShowTarget(true);
	//pUnit->getPositionComponent()->setPosition(Vector2D(100, 100));
	//pUnit->setSteering(Steering::FLOCKING, Vector2D(500, 300));
	std::cout << "For editing weights please consult weights.txt First line is cohesion, second line is alignment, third line is seperation, fourth line is the general drift.\n";
	return true;
}

void Game::cleanup(){
	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	delete mpFont;
	mpFont = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpMessageManager;
	mpMessageManager = NULL;
	delete mpUnitManager;
	mpUnitManager = NULL;
	delete mpComponentManager;
	mpComponentManager = NULL;
	delete inSys;
	inSys = NULL;
}

void Game::beginLoop(){
	mpLoopTimer->start();
}

const float TARGET_ELAPSED_MS = LOOP_TARGET_TIME / 1000.0f;
	
void Game::processLoop(){

	mpUnitManager->updateAll(TARGET_ELAPSED_MS);
	mpComponentManager->update(TARGET_ELAPSED_MS);
	
	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite( BACKGROUND_SPRITE_ID );
	GraphicsBuffer* pDest = mpGraphicsSystem->getBackBuffer();
	mpGraphicsSystem->draw(*pDest, *pBackgroundSprite, 0.0f, 0.0f);

	//draw units
	mpUnitManager->drawAll();

	SDL_PumpEvents();
	int x, y;
	SDL_GetMouseState(&x, &y);

	//create mouse text
	std::stringstream mousePos;
	mousePos << x << ":" << y;

	//write text at mouse position
	mpGraphicsSystem->writeText(*mpFont, (float)x + 12, (float)y - 3, mousePos.str(), BLACK_COLOR);

	//test of fill region
	//mpGraphicsSystem->fillRegion(*pDest, Vector2D(300, 300), Vector2D(500, 500), RED_COLOR);
	mpGraphicsSystem->swap();

	mpMessageManager->processMessagesForThisframe();

	inSys->Update();

	std::string input;
	float newNum;
	infile.open("weights.txt");

	getline(infile, input);
	newNum = std::stof(input);
	cohereWeight = newNum;

	getline(infile, input);
	newNum = std::stof(input);
	alignWeight = newNum;

	getline(infile, input);
	newNum = std::stof(input);
	seperateWeight = newNum;

	getline(infile, input);
	newNum = std::stof(input);
	driftWeight = newNum;

	infile.close();
}

bool Game::endLoop(){
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed(LOOP_TARGET_TIME);
	return mShouldExit;
}

float genRandomBinomial(){
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat(){
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}