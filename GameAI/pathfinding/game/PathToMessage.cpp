#include "PathToMessage.h"
#include "Game.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "Grid.h"
#include "GridGraph.h"

PathToMessage::PathToMessage(const Vector2D& from, const Vector2D& to):GameMessage(PATH_TO_MESSAGE), from(from), to(to){}

PathToMessage::~PathToMessage(){}

void PathToMessage::Process(){
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if(pGame != NULL){
		GridPathfinder* pPathfinder = pGame->GetPathfinder();
		GridGraph* pGridGraph = pGame->GetGridGraph();
		Grid* pGrid = pGame->GetGrid();
		int fromIndex = pGrid->getSquareIndexFromPixelXY( (int)from.getX(), (int)from.getY() );
		int toIndex = pGrid->getSquareIndexFromPixelXY( (int)to.getX(), (int)to.getY() );
		Node* pFromNode = pGridGraph->getNode( fromIndex );
		Node* pToNode = pGridGraph->getNode( toIndex );
		pPathfinder->FindPath( pFromNode, pToNode );
	}
}
