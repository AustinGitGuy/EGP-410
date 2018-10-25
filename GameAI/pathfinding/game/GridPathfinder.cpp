#include "GridPathfinder.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "Path.h"
#include "Game.h"
#include "GraphicsBuffer.h"
#include "Color.h"
#include <cassert>
#include <iostream>

using namespace std;

GridPathfinder::GridPathfinder(GridGraph* pGraph):Pathfinder(pGraph),timeElapsed(0.0){
#ifdef VISUALIZE_PATH
	visualizer = NULL;
	mPath = NULL;
#endif
}

GridPathfinder::~GridPathfinder(){
#ifdef VISUALIZE_PATH
	delete visualizer;
#endif
}

float lerp(int value, int start, int end){
	//returns float representing how far value is between start and end
	assert(start <= end);

	float lerpVal = 0.0f;

	if(start <= end){
		int range = end - start;
		lerpVal = value / (float)range;
	}
	return lerpVal;
}


#ifdef VISUALIZE_PATH
void GridPathfinder::DrawVisualization(Grid* pGrid, GraphicsBuffer* pDest){

	//Dean buggered this function. Angry

	delete visualizer;
	visualizer = new GridVisualizer( pGrid );
	static Color pathColor = Color(255,64,64);
	static Color visitedColor = GREEN_COLOR;
	static Color startColor = Color(1,255,128);
	static Color stopColor = Color(1,128,255);

	if(mPath != NULL){
		Color currentPathColor = pathColor;
		int numNodes = mPath->GetNumNodes();
		for(int i = 1; i < numNodes - 1; i++){
			visualizer->addColor(mPath->PeekNode(i)->GetID(), currentPathColor);
			float lerpVal = lerp(i, 0, numNodes);
			currentPathColor = Color((int)(255 * (1.0f - lerpVal)), currentPathColor.getG(), currentPathColor.getB());
		}

		//add beginning and ending color
		visualizer->addColor(mPath->PeekNode(0)->GetID(), startColor);
		visualizer->addColor( mPath->PeekNode( mPath->GetNumNodes()-1 )->GetID(), stopColor );
	}

	visualizer->Draw(*pDest);
}
#endif