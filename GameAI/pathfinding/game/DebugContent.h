#pragma once

#include <string>
#include <Trackable.h>

class DebugContent : public Trackable {
public:
	DebugContent(){};
	virtual ~DebugContent(){};

	virtual std::string GetDebugString() = 0;
};