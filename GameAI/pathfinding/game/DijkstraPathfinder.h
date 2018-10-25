#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DijkstraPathfinder : public GridPathfinder {
public:
	DijkstraPathfinder(Graph* pGraph);
	~DijkstraPathfinder();

	//This is just a basic Dijkstra Pathfinder, not much liberties were taken. It is pretty much just the DFP but with some consitencies to fix crashes.
	Path* FindPath(Node* fromNode, Node* toNode); //make sure to delete the mPath when you are done!

private:
};

