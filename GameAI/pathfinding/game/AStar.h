#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class AStar : public GridPathfinder {
public:
	AStar(Graph* pGraph);
	~AStar();

	Path* FindPath(Node* fromNode, Node* toNode); //make sure to delete the mPath when you are done!
	float Guestimate(Node* fromNode, Node* toNode);

private:
};

