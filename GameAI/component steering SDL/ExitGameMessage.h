#include "GameMessage.h"

class ExitGameMessage :public GameMessage {
public:
	ExitGameMessage(const bool& doExit);
	~ExitGameMessage();

	void process();

private:
	bool exit;
};