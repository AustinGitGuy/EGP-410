#include "GameMessage.h"

class AddUnitMessage :public GameMessage {
public:
	AddUnitMessage(int num);
	~AddUnitMessage();

	void process();

private:
	int numUnits;
};