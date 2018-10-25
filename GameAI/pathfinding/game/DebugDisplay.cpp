#include "DebugDisplay.h"
#include "GraphicsBuffer.h"
#include "DebugContent.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "Color.h"

using namespace std;

DebugDisplay::DebugDisplay(const Vector2D& pos, DebugContent* pContent):pos(pos),debugContent(pContent){}

DebugDisplay::~DebugDisplay(){
	delete debugContent;
}

void DebugDisplay::Draw(GraphicsBuffer* pBuffer){
	string toDisplay = debugContent->GetDebugString();
	gpGame->getGraphicsSystem()->writeText(*pBuffer, *(gpGame->getFont()), pos.getX(), pos.getY(), toDisplay, BLACK_COLOR);
}
