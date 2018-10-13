#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

DijkstraPathfinder::DijkstraPathfinder(Graph* pGraph):GridPathfinder(dynamic_cast<GridGraph*>(pGraph)){
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif

}

DijkstraPathfinder::~DijkstraPathfinder(){
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}