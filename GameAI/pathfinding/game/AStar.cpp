#include "AStar.h"
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
#include "GameApp.h"
#include "Vector2D.h"
#include "Grid.h"

AStar::AStar(Graph* pGraph):GridPathfinder(dynamic_cast<GridGraph*>(pGraph)){
#ifdef VISUALIZE_PATH
	mPath = NULL;
#endif
}

AStar::~AStar(){
#ifdef VISUALIZE_PATH
	delete mPath;
#endif
}

//A lot of the stuff from here was taken from my DijkstraPathfinder (obviously)
//This is the basic A* which uses the DijkstraPathfinder algorithm but then combines a simple guestimate algorithm
Path* AStar::FindPath(Node* fromNode, Node* toNode){
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit priority queue and place starting node in it
	PriorityQueue<Node*, std::vector<Node*>, Compare> nodesToVisit;
	fromNode->SetWeight(0); //We can always go from where we are to where we are
	nodesToVisit.push(fromNode);

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
				if(!toNodeAdded){
					float heuristic = Guestimate(tempNode, toNode);

					//Need to spice this up from dijkstra because you need to revisit lists
					if(path->ContainsNode(tempNode)){
						if(tempNode->GetWeight() > pConnection->GetWeight() + currentNode->GetWeight()){
							tempNode->SetPrevNode(currentNode);
							tempNode->SetWeight(pConnection->GetWeight() + currentNode->GetWeight());
							tempNode->SetHeuristic(heuristic);
						}
					}
					//This is the normal time
					else if(nodesToVisit.find(tempNode) == nodesToVisit.end()){
						tempNode->SetPrevNode(currentNode);
						tempNode->SetWeight(pConnection->GetWeight() + currentNode->GetWeight());
						tempNode->SetHeuristic(heuristic);
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
		}

		Node* prevNode = toNode;

#ifdef VISUALIZE_PATH
		delete path;
		path = new Path();
		while(prevNode != fromNode){
			path->AddNode(prevNode);
			prevNode = prevNode->GetPrevNode();
			if(prevNode == nullptr){
				prevNode = fromNode;
			}
		}
	}
#endif
	gpPerformanceTracker->stopTracking("path");
	timeElapsed = gpPerformanceTracker->getElapsedTime("path");
#ifdef VISUALIZE_PATH
	mPath = path;
#endif
	return path;
}

//Uses the simple crow fly. The distance is using this funky cornerofsquare I learned about. The function seems a bit weird but its Deans function not mine.
float AStar::Guestimate(Node* fromNode, Node* toNode){
	Grid* gridBoi = dynamic_cast<GameApp*>(gpGame)->GetGrid(); //Get the grid boi
	return (gridBoi->getULCornerOfSquare(fromNode->GetID()) - gridBoi->getULCornerOfSquare(toNode->GetID())).getLength();
}