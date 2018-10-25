#pragma once

#include <Trackable.h>

enum MessageType {
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	PATH_TO_MESSAGE = 1
};

class GameMessage: public Trackable {
public:
	friend class GameMessageManager;

	GameMessage(MessageType type );
	~GameMessage();

	double GetSubmittedTime() const {return submittedTime;};
	double GetScheduledTime() const {return scheduledTime;};

protected:
	MessageType messageType;
	double submittedTime;
	double scheduledTime;

private:
	virtual void Process() = 0; 
};


