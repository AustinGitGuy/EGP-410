#pragma once

#include <Trackable.h>
#include <Vector2D.h>

class DebugContent;
class GraphicsBuffer;

class DebugDisplay:public Trackable {
public:
	DebugDisplay(const Vector2D& pos, DebugContent* pContent);
	~DebugDisplay();

	void Draw(GraphicsBuffer* pBuffer);

private:
	DebugContent* debugContent;
	Vector2D pos;

};