//This is the other one going around, a simple compare for the queue. https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
#pragma once
#include "Node.h"

class Compare {
public:
	//Basically just compares two nodes to see which cost is greater and returns a true/false
	bool operator() (Node* node1, Node* node2){
		return node1->GetWeight() > node2->GetWeight();
	}
};