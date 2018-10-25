#include "DepthFirstPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

DepthFirstPathfinder::DepthFirstPathfinder(Graph* pGraph):GridPathfinder(dynamic_cast<GridGraph*>(pGraph)){
#ifdef VISUALIZE_PATH
	mPath = NULL;
#endif

}

DepthFirstPathfinder::~DepthFirstPathfinder(){
#ifdef VISUALIZE_PATH
	delete mPath;
#endif
}

//This is the main findpath function included in Deanlib
Path* DepthFirstPathfinder::FindPath(Node* pFrom, Node* pTo){
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it
	list<Node*> nodesToVisit;
	nodesToVisit.push_front(pFrom);

#ifdef VISUALIZE_PATH
	delete mPath;
	visitedNodes.clear();
	visitedNodes.push_back(pFrom);
#endif
	
	//create Path
	Path* pPath = new Path();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while(pCurrentNode != pTo && nodesToVisit.size() > 0){
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();
		//add Node to Path
		pPath->AddNode(pCurrentNode);

		//get the Connections for the current node
		vector<Connection*> connections = graph->getConnections(pCurrentNode->GetID());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for(unsigned int i=0; i<connections.size(); i++){
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->GetToNode();
			if(!toNodeAdded && !pPath->ContainsNode(pTempToNode) && find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode) == nodesToVisit.end()){
				nodesToVisit.push_front( pTempToNode );//uncomment me for depth-first search
				//nodesToVisit.push_back( pTempToNode );//uncomment me for breadth-first search
				if(pTempToNode == pTo){
					toNodeAdded = true;
				}
#ifdef VISUALIZE_PATH
				visitedNodes.push_back(pTempToNode);
#endif
			}
		}
	}
	
	gpPerformanceTracker->stopTracking("path");
	timeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mPath = pPath;
#endif
	return pPath;

}

