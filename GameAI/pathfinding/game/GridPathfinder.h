#pragma once

#include "Pathfinder.h"
class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder:public Pathfinder {
public:
	friend class PathfindingDebugContent;

	GridPathfinder(GridGraph* pGraph);
	virtual ~GridPathfinder();

	virtual Path* FindPath(Node* pFrom, Node* pTo) = 0;
	
#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void DrawVisualization(Grid* pGrid, GraphicsBuffer* pDest);
protected:
	std::vector<Node*> visitedNodes;
	Path* mPath;
	GridVisualizer* visualizer;
#endif

	double timeElapsed;
};