#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class PathToMessage:public GameMessage {
public:
	PathToMessage(const Vector2D& from, const Vector2D& to);
	~PathToMessage();

	const Vector2D& GetFrom() const {return from;};
	const Vector2D& GetTo() const {return to;};

	void Process();

private:
	Vector2D from;
	Vector2D to;
};