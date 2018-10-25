#pragma once

#include <Trackable.h>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node:public Trackable {
public:
	Node(const NODE_ID& id);
	Node();
	~Node();

	const NODE_ID& GetID() const {return id;};
	float GetWeight(){return weight;};
	float GetHeuristic(){return heuristic;};
	void SetHeuristic(float newHeur){heuristic = newHeur;};
	void SetWeight(float newWeight){weight = newWeight;};
	void SetPrevNode(Node* node){prevNode = node;};
	Node* GetPrevNode(){return prevNode;};

private:
	float weight;
	float heuristic;
	const NODE_ID id;
	Node* prevNode = NULL;
};