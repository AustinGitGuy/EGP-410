#pragma once

#include <vector>
#include <Trackable.h>

class Node;

class Path : public Trackable {
public:
	Path();
	~Path();

	Node* PeekNode(int index) const;
	Node* PeekNextNode() const;
	Node* GetAndRemoveNextNode();
	bool ContainsNode(Node* pNode);
	int GetNumNodes() const {return nodes.size();};

	void AddNode(Node* pNode);

private:
	std::vector<Node*> nodes;
};