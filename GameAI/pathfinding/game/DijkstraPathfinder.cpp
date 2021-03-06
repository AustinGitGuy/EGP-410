#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include "PriorityQueue.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include "Compare.h"

DijkstraPathfinder::DijkstraPathfinder(Graph* pGraph):GridPathfinder(dynamic_cast<GridGraph*>(pGraph)){
	#ifdef VISUALIZE_PATH
	mPath = NULL;
	#endif
}

DijkstraPathfinder::~DijkstraPathfinder(){
	#ifdef VISUALIZE_PATH
	delete mPath;
	#endif
}

//This is just a basic pathfinder we learned in class. Most differences are listed in comments
Path* DijkstraPathfinder::FindPath(Node* fromNode, Node* toNode){
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit priority queue and place starting node in it
	PriorityQueue<Node*, std::vector<Node*>, Compare> nodesToVisit;
	fromNode->SetWeight(0); //We can always go from where we are to where we are
	nodesToVisit.push(fromNode);

	//A lot of the stuff from here was taken from DepthFirstPathfinder with a few modifications to make variable names easier to read
	//PriorityQueue syntax was taken from http://www.cplusplus.com/reference/queue/priority_queue/

#ifdef VISUALIZE_PATH
	delete mPath;
	visitedNodes.clear();
	visitedNodes.push_back(fromNode);
#endif

	//create Path
	Path* path = new Path();

	Node* currentNode = NULL;
	bool toNodeAdded = false;

	//It was throwing an error if the node was the same as the start node so this fixes it
	if(fromNode->GetID() == toNode->GetID()){
		path->AddNode(fromNode);
	}
	else {
		while(currentNode != toNode && nodesToVisit.size() > 0){
			currentNode = nodesToVisit.top();
			nodesToVisit.pop();
			path->AddNode(currentNode);
			std::vector<Connection*> connections = graph->getConnections(currentNode->GetID());

			//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
			for(int i=0; i < connections.size(); i++){
				Connection* pConnection = connections[i];
				Node* tempNode = connections[i]->GetToNode();

				//This replaced the find from list with find from the new PriorityQueue
				if(!toNodeAdded && !path->ContainsNode(tempNode) && nodesToVisit.find(tempNode) == nodesToVisit.end()){
					tempNode->SetPrevNode(currentNode);
					tempNode->SetWeight(pConnection->GetWeight() + currentNode->GetWeight());
					nodesToVisit.push(tempNode);
					if(tempNode == toNode){
						toNodeAdded = true;
					}
#ifdef VISUALIZE_PATH
					visitedNodes.push_back(tempNode);
#endif
				}
			}
		}

		//The game will crash if the numnodes are 0 and it tries to generate a mPath
		if(path->GetNumNodes() <= 0){
			delete path;
			path = NULL;
			mPath = path;
			return path;
		}
		Node* prevNode = toNode;

#ifdef VISUALIZE_PATH
		//Since the normal visualization puts every node in the mPath, this only puts the mPath in the mPath.
		delete path;
		path = new Path();
		while(prevNode != fromNode){
			path->AddNode(prevNode);
			prevNode = prevNode->GetPrevNode();
			//The game will also crash if you try to grab a null node
			if(prevNode == NULL){
				prevNode = fromNode;
			}
		}
#endif
	}

	gpPerformanceTracker->stopTracking("path");
	timeElapsed = gpPerformanceTracker->getElapsedTime("path");
#ifdef VISUALIZE_PATH
	mPath = path;
#endif
	return path;
}