
#include <sstream>
#include <ctime>
#include <cstdlib>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Font.h"
#include <Timer.h>
#include "Defines.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;

Game::Game()
	:mpGraphicsSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mShouldExit(false)
	,mpFont(NULL)
	,mLoopTargetTime(0.0f)
{
}

Game::~Game()
{
	Cleanup();
}

bool Game::Init()
{
	srand((UINT)time(0));//seed random number generator

	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;


	//create and Init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->Init(WIDTH, HEIGHT);
	if (!goodGraphics)
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager(mpGraphicsSystem);
	mpSpriteManager = new SpriteManager();

	
	//load background
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, "wallpaper.bmp");

	//load Font
	mpFont = new Font("cour.ttf", 24);

	return true;
}

void Game::Cleanup()
{
	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	//Cleanup font
	delete mpFont;
	mpFont = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
}

void Game::BeginLoop()
{
	mpLoopTimer->start();

	//Draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite( BACKGROUND_SPRITE_ID );
	mpGraphicsSystem->Draw(*pBackgroundSprite, 0.0f, 0.0f);
}

void Game::ProcessLoop()
{
		mpGraphicsSystem->swap();
}

bool Game::EndLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( mLoopTargetTime );
	return mShouldExit;
}


float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

float mapRotationToRange( float rotation, float low, float high )
{
	while( rotation < low )
	{
		rotation += ( 2.0f * (float)PI );
	}

	while( rotation > high )
	{
		rotation -= ( 2.0f * (float)PI );
	}
	return rotation;
}
