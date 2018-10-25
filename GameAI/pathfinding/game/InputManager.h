#pragma once
#include "Trackable.h"

class InputManager : public Trackable {
public:
	InputManager();
	~InputManager();
	void Update();
};