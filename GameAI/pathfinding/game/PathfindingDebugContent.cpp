#include "PathfindingDebugContent.h"
#include "GridPathfinder.h"
#include "Path.h"
#include <sstream>

using namespace std;

PathfindingDebugContent::PathfindingDebugContent(GridPathfinder* pPathfinder):gridPathfinder(pPathfinder){}

string PathfindingDebugContent::GetDebugString(){
	stringstream theStream;

#ifdef VISUALIZE_PATH
	if(gridPathfinder->mPath != NULL){
		theStream << "Pathlength:"<< gridPathfinder->mPath->GetNumNodes();
	}
	
	theStream << "  Num Nodes Processed:" << gridPathfinder->visitedNodes.size();
#endif
	theStream << "  Elapsed Time:" << gridPathfinder->timeElapsed;
	return theStream.str();
}

