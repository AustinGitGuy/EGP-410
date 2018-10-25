#pragma once

#include "GridPathfinder.h"
#include <vector>

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DepthFirstPathfinder : public GridPathfinder {
public:
	DepthFirstPathfinder(Graph* pGraph);
	~DepthFirstPathfinder();

	Path* FindPath(Node* pFrom, Node* pTo); //make sure to delete the mPath when you are done!

private:
};

