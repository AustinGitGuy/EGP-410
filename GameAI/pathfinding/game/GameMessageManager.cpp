#include <list>

#include "Game.h"
#include "GameMessageManager.h"
#include "GameMessage.h"

using namespace std;

GameMessageManager::GameMessageManager(){}

GameMessageManager::~GameMessageManager(){
	list<GameMessage*>::iterator iter;
	for(iter = messageList.begin(); iter != messageList.end(); ++iter){
		delete (*iter);
	}
}

void GameMessageManager::ProcessMessagesForThisFrame(){
	double currentTime = gpGame->getCurrentTime();

	list<GameMessage*>::iterator iter = messageList.begin();
	while(iter != messageList.end()){
		if((*iter)->GetScheduledTime() <= currentTime){
			(*iter)->Process();
			delete (*iter);
			iter = messageList.erase(iter);
		}
		else {
			++iter;
		}
	}
}

void GameMessageManager::AddMessage(GameMessage* pMessage, int delay){
	double currentTime = gpGame->getCurrentTime();

	//set frame numbers
	pMessage->submittedTime = currentTime;
	pMessage->scheduledTime = currentTime + delay;

	//put it in the message list
	messageList.push_back(pMessage);
}